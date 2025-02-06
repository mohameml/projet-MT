#!/bin/bash

# Définition des chemins relatifs
EXECUTABLE="../build/hedging_portfolio"

# Liste des tests à exécuter (chaque ligne contient: params_file market_file output_file)
TASKS=(
    "../data/call_currency/call_currency_params.json ../data/call_currency/call_currency_market.csv ./call_currency_res.json"
    "../data/call_quanto/call_quanto_params.json ../data/call_quanto/call_quanto_market.csv ./call_quanto_res.json"
    "../data/foreign_asian/foreign_asian_params.json ../data/foreign_asian/foreign_asian_market.csv ./foreign_asian_res.json"
    "../data/quanto_exchange/quanto_exchange_params.json ../data/quanto_exchange/quanto_exchange_market.csv ./quanto_exchange_res.json"
    "../data/foreign_perf_basket/foreign_perf_basket_params.json ../data/foreign_perf_basket/foreign_perf_basket_market.csv ./foreign_perf_basket_res.json"
)

# Exécution des tâches
for task in "${TASKS[@]}"; do
    echo "=============================== Lancement : $EXECUTABLE $task ================================="
    $EXECUTABLE $task

    # Vérification du succès
    if [ $? -eq 0 ]; then
        echo "Succès ✅ : $task"
    else
        echo "Erreur ❌ : $task" >&2
    fi
    echo "--------------------------------"
done

echo "Tous les calculs sont terminés."
