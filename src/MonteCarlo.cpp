#include "MonteCarlo.hpp"
#include <nlohmann/json.hpp>

MonteCarlo::MonteCarlo(const nlohmann::json json)
{
    json.at("SampleNb").get_to(sample_number);
    json.at("RelativeFiniteDifferenceStep").get_to(fd_step);

    model = new GlobalModel(json);
    option = instance_option(json);
    rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, time(NULL));
}