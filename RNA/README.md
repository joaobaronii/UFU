# 📈 Previsão de Volatilidade do Bitcoin: TFT vs LSTM vs GARCH

Este repositório contém o código-fonte, os pipelines de pré-processamento e a pesquisa documentada do artigo **"Previsão de Volatilidade do Bitcoin: Um Estudo Comparativo entre Temporal Fusion Transformers, LSTM e GARCH"**. 

O objetivo central deste projeto é investigar e avaliar arquiteturas de redes neurais do estado-da-arte na previsão de risco financeiro, especificamente a volatilidade diária do Bitcoin com um horizonte de 24 horas à frente.

## 🧠 Visão Geral dos Modelos Investigados

O estudo contrasta três abordagens distintas para lidar com séries temporais financeiras:
* **Temporal Fusion Transformer (TFT):** Arquitetura moderna baseada em atenção, destacando-se pelo uso da *Variable Selection Network* (VSN) para ponderar dinamicamente a relevância de variáveis exógenas heterogêneas.
* **Long Short-Term Memory (LSTM):** Rede neural recorrente profunda (RNN) clássica, capaz de mitigar o desaparecimento do gradiente e capturar dependências não lineares e de longo prazo.
* **GARCH(1,1):** *Baseline* econométrico univariado consolidado, focado em modelar o agrupamento de volatilidade (*volatility clustering*).

## 📊 Dataset e Pré-processamento

Para refletir a dinâmica atual, o estudo utiliza uma abordagem multivariada com dados de fechamento de granularidade horária abrangendo um histórico de 730 dias, de 2024 a 2026[cite: 245, 258].

* **Ativo Alvo:** Bitcoin (BTC-USD).
* **Variáveis Exógenas (Contexto de Mercado):** ETH-USD, SOL-USD, e ações do setor de tecnologia tradicionais (NVDA, AAPL, MSFT, GOOGL, QQQ).
* **Aquisição Reprodutível:** Dados extraídos de forma programática utilizando a API do Yahoo Finance via biblioteca `yfinance` em Python.
* **Alinhamento Temporal:** Aplicação de redimensionamento forçando a marcação de hora cheia e preenchimento de lacunas com o método *forward fill* para sincronizar o mercado de criptomoedas com as restrições de horário do mercado de ações.
* **Engenharia de Atributos:** Transformação de preços originais em retornos logarítmicos, e cálculo de indicadores técnicos como Volatilidade Móvel (24h) e RSI de 14 períodos.
* **Sequenciamento Temporal:** Divisão estrita de 80% para treino e 20% para teste cronológico, com as redes neurais utilizando uma janela de observação (*lookback window*) de 168 horas (uma semana).

## 🏆 Principais Resultados

Os testes empíricos demonstraram que a transição de modelos estatísticos univariados para arquiteturas profundas multivariadas traz ganhos significativos:

* **TFT (Estado-da-Arte):** Registrou o menor erro global com um **RMSE de 0.0100**.Conseguiu minimizar os erros preditivos ao filtrar o ruído das ações de tecnologia e ponderar a influência de choques passados.
* **LSTM:** Alcançou um **RMSE de 0.0108**, validando a capacidade de aprendizado não linear, mas sofreu com atraso na atualização de pesos durante picos extremos.
* **GARCH(1,1):** Obteve o maior erro com um **RMSE de 0.0263**, demonstrando dificuldade em reagir a quebras estruturais e em incorporar sinais multivariados complexos.

## 🚀 Trabalhos Futuros

Como próximos passos indicados na pesquisa, sugere-se a expansão do *dataset* com processamento de linguagem natural (análise de sentimento) sobre notícias e redes sociais, além da exploração de *Quantile Loss* para o modelo TFT, visando a geração de intervalos de confiança.

## 👥 Autores

Trabalho desenvolvido no curso de Bacharelado em Ciência da Computação - Universidade Federal de Uberlândia (UFU):
* João Pedro Costa Baroni
* Leonardo Henrique Carvalho Oliveira 
* Matheus Henrique Barbosa Ribeiro 
* Rodrigo Otávio Fernandes Rodrigues 
* Yan Lucas Santos Marra 

---
*Para mais detalhes matemáticos e estruturais sobre a pesquisa, consulte o artigo completo (`Paper.pdf`) disponibilizado neste repositório.*
