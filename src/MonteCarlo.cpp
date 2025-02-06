#include "MonteCarlo.hpp"
#include <nlohmann/json.hpp>

MonteCarlo::MonteCarlo()
{
}

MonteCarlo::MonteCarlo(const nlohmann::json json)
{
    json.at("SampleNb").get_to(sample_number);
    json.at("RelativeFiniteDifferenceStep").get_to(fd_step);

    model = new GlobalModel(json);
    option = instance_option(json);

    model_size = model->assets.size() + model->currencies.size();

    nbDays = json.at("Option").at("MaturityInDays").get<int>();
    numberOfDaysPerYear = json.at("NumberOfDaysInOneYear").get<int>();

    rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, time(NULL));
}

MonteCarlo::~MonteCarlo()
{
    delete option ;
    delete model;
    pnl_rng_free(&rng);
}

void MonteCarlo::priceAndDelta(int t, const PnlMat *Past, double& price , double& price_std , PnlVect* deltas_vect , PnlVect*  stddev_deltas_vect)
{
    int D = model_size;
    int M = sample_number;
    int N = model->monitoringTimeGrid.len();
    double h = fd_step;
    

    PnlMat *path = pnl_mat_create(N, D);

    for (int i = 0; i < M; i++)
    {

        model->asset(Past, t , path, this->rng);
        
        double phi_j = this->option->payOff(path);
        price += phi_j;
        price_std += phi_j * phi_j;

        for (int d = 0; d < D; d++)
        {
            double diff_payoff = 0.0;
            model->shift_asset(d, t , 1.0 + h, path);
            diff_payoff += option->payOff(path);
            model->shift_asset(d, t , (1.0 - h) / (1.0 + h), path);
            diff_payoff -= option->payOff(path);
            model->shift_asset(d, t , 1.0 / (1.0 - h), path);
            LET(deltas_vect, d) += diff_payoff;
            LET(stddev_deltas_vect, d) += diff_payoff * diff_payoff;
        }
    }

    double t_ = (double) t / (double) numberOfDaysPerYear;
    end_of_calcul_price(price, price_std, t_);
    PnlVect St = pnl_vect_wrap_mat_row(Past, Past->m - 1);
    end_of_calcul_delta(deltas_vect, stddev_deltas_vect, t_, &St);

    pnl_mat_free(&path);
}

void MonteCarlo::end_of_calcul_price(double &price, double &price_stdev, double t) const
{
    double r = model->domesticInterestRate.rate;
    double T = option->maturity;
    double M = sample_number;
    price = std::exp(-r * (T - t)) * price / M;
    price_stdev = price_stdev * std::exp(-2.0 * r * (T - t)) / M - price * price;
    price_stdev = std::sqrt(std::abs(price_stdev / M));
}

void MonteCarlo::end_of_calcul_delta(PnlVect *delta, PnlVect *delta_stdev, double t, PnlVect *St) const
{
    double M = sample_number;
    double r = model->domesticInterestRate.rate;
    double T = option->maturity;
    double h = fd_step;

    // fin de calcul de delta :
    pnl_vect_mult_scalar(delta, std::exp(-r * (T - t)) / (2.0 * h * M));
    pnl_vect_div_vect_term(delta, St);

    // fin de calcul de delta_std_dev :
    pnl_vect_mult_scalar(delta_stdev, std::exp(-2.0 * r * (T - t)) / (4.0 * M * h * h));
    pnl_vect_div_vect_term(delta_stdev, St);
    pnl_vect_div_vect_term(delta_stdev, St);
    PnlVect *delta_copy = pnl_vect_copy(delta);
    pnl_vect_mult_vect_term(delta_copy, delta);
    pnl_vect_minus_vect(delta_stdev, delta_copy);
    pnl_vect_div_double(delta_stdev, M);
    // pnl_vect_map_inplace(delta_stdev, std::sqrt);
    for (size_t i = 0; i < delta_stdev->size; i++)
    {
        LET(delta_stdev , i) = std::sqrt(std::abs(GET(delta_stdev , i)));
    }
    

    pnl_vect_free(&delta_copy);
}