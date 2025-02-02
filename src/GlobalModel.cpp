#include "GlobalModel.hpp"

GlobalModel::GlobalModel()
{
}

GlobalModel::~GlobalModel()
{
}


GlobalModel::GlobalModel(const nlohmann::json json)
{
}

void GlobalModel::asset(PnlMat *path, PnlRng *rng)
{
}

void GlobalModel::asset(const PnlMat *past, double t, double T, PnlMat *path, PnlRng *rng)
{
}

void GlobalModel::shift_asset(int d, double h, PnlMat *original_paths)
{
}

void GlobalModel::shift_asset(int d, double t, double h, PnlMat *original_paths)
{
}
