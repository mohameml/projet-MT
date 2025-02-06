#!/bin/bash

# Définition des chemins relatifs
EXECUTABLE="../build/hedging_portfolio"

# Liste des tests à exécuter (chaque ligne contient: params_file market_file output_file)
TASKS=(
    "../data-eval/call_currency/call_currency_params.json ../data-eval/call_currency/call_currency_market.csv ../Equipe_3/output/call_currency_portfolio.json"
    "../data-eval/call_quanto/call_quanto_params.json ../data-eval/call_quanto/call_quanto_market.csv ../Equipe_3/output/call_quanto_portfolio.json"
    "../data-eval/foreign_asian/foreign_asian_params.json ../data-eval/foreign_asian/foreign_asian_market.csv ../Equipe_3/output/foreign_asian_portfolio.json"
    "../data-eval/quanto_exchange/quanto_exchange_params.json ../data-eval/quanto_exchange/quanto_exchange_market.csv ../Equipe_3/output/quanto_exchange_portfolio.json"
    "../data-eval/foreign_perf_basket/foreign_perf_basket_params.json ../data-eval/foreign_perf_basket/foreign_perf_basket_market.csv ../Equipe_3/output/foreign_perf_basket_portfolio.json"
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
