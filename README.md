عالیه! برو این کارا رو دقیقاً به ترتیب انجام بده (۱ دقیقه طول می‌کشه):

### ۱) برو تو GitHub و یه repo جدید بساز
```
https://github.com/new
```
اسم repo رو بذار:
```
observability-fintech
```
تیک Public بزن  
تیک "Add a README file" رو **بردار** (ما خودمون می‌ذاریم)

### ۲) کل متن زیر رو کامل کپی کن (از خط اول تا آخر)

```markdown
# Observability Fintech (DevOps + Prometheus/Grafana/Loki)

A complete observability demo for a financial transactions service (Flask + Gunicorn) using **Prometheus/Alertmanager**, **Grafana**, **Loki/Promtail**, **Node Exporter**, and **cAdvisor**, all orchestrated with Docker Compose.

The project focuses on finance-relevant KPIs/SLIs (TPS, Success/Error rate, Avg/p95 latency, Revenue/min, Gateway errors, Backpressure) and low-noise alerting (Telegram + webhook → audit trail in logs).

## Features

- App metrics exposed via Prometheus client (Counter/Gauge/Histogram)
- Finance dashboard in Grafana (TPS, Error%, Avg/p95 latency, Revenue/min, In-flight)
- Alerting (warning/critical) with fan-out to Telegram (human) + Flask webhook (system log trail)
- Centralized logs with Promtail → Loki (+ ready-to-use LogQL filters)
- Infra visibility via Node Exporter & cAdviso
- Traffic generator (`loadgen.sh`) and controlled load test (`load_test.py`)
- Persistent volumes for Prometheus/Grafana/Loki data

## Architecture

```ascii
Client  →  Flask+Gunicorn (/transaction, /metrics, /alert)
             │            │             │
             │            │             └─ logs {"event":"alert_received"} → Loki
             │            └─ Prometheus scrapes /metrics
             │
loadgen  →  synthetic traffic

Node Exporter & cAdvisor → Prometheus

Prometheus (rules) ──FIRING──> Alertmanager ──┬── Telegram (human)
                                              └── Webhook /alert (audit trail)
Grafana ← Prometheus + Loki (Dashboards & Logs)
```

![Architecture](docs/architecture.png)

## Repository Layout

```
observability-fintech
├── app/                       # Flask app (service under test)
│   ├── app.py                 # endpoints + metrics
│   ├── Dockerfile
│   └── requirements.txt
├── docker-compose.yml         # orchestration
├── grafana/
│   └── provisioning/
│       ├── dashboards/
│       │   ├── dashboards.yml
│       │   ├── fintech-dashboard.json
│       │   ├── node-exporter-1860.json
│       │   └── docker-cadvisor-13496.json
│       └── datasources/
│           ├── datasource.yml
│           └── loki.yml
├── loki/config.yml
├── prometheus/
│   ├── prometheus.yml
│   ├── alerts.yml
│   └── alertmanager.yml
├── promtail/config.yml
└── scripts/
    ├── loadgen.sh
    └── load_test.py
```

## Prerequisites

- Docker + Docker Compose
- Open ports: 3000, 3100, 5000, 8080, 9090, 9093, 9100
- (Optional) Telegram bot token and chat ID for alert notifications

## Quick Start

```bash
# 1) Clone
git clone https://github.com/<you>/observability-fintech.git
cd observability-fintech

# 2) (Optional) set Telegram secrets
export AM_TELEGRAM_BOT_TOKEN="xxxx"
export AM_TELEGRAM_CHAT_ID="123456"

# 3) Up & build
docker compose up -d --build

# 4) Health checks
curl -sf localhost:5000/health && echo "APP OK"
curl -sf localhost:9090/-/ready && echo "PROM OK"
curl -sf localhost:3000/login  && echo "GRAFANA OK"
```

### URLs
- App: http://localhost:5000
- Prometheus: http://localhost:9090
- Alertmanager: http://localhost:9093
- Grafana: http://localhost:3000 (admin/admin)
- Loki: http://localhost:3100

## Configuration Notes

### App (Flask)
- `POST /transaction` — payment simulation
- `GET /metrics` — Prometheus
- `POST /alert` — webhook for audit trail
- Metrics: `transactions_total`, `transaction_latency_seconds`, `transaction_amount`, `transactions_in_progress`, etc.

### Alertmanager
Fan-out to:
- Telegram
- Webhook → `http://fintech_flask:5000/alert`

### Grafana
Pre-provisioned dashboards:
- Fintech Dashboard
- Node Exporter
- cAdvisor

### Loki + Promtail
```logql
{container="fintech_flask"} |= "alert_received"
```

## Key PromQL Queries

```promql
# TPS
sum(rate(transactions_total[1m]))

# Error rate
sum(rate(transactions_total{status="failed"}[5m])) / 
clamp_min(sum(rate(transactions_total[5m])), 1e-9)

# p95 latency
histogram_quantile(0.95, sum by (le)(rate(transaction_latency_seconds_bucket[5m])))

# Revenue/min
sum(rate(transaction_amount_sum[5m])) * 60
```

## Screenshots

![Project tree](docs/tree.png)
![docker ps](docs/docker-ps.png)
![Prometheus Targets](docs/prom-targets.png)
![Grafana Dashboard](docs/grafana-fintech.png)
![Logs panel](docs/grafana-logs.png)
![Telegram alert](docs/telegram.png)

## Security Notes
- Never commit real Telegram tokens
- Change Grafana default password
- Use Docker volumes for persistence

## Testing

```bash
python3 scripts/load_test.py --rps 20 --duration 300
```

## License
MIT License

---

**Star this repo if you liked it!**
```

### ۳) حالا اینو بذار تو README.md

۱. تو repo جدیدت برو  
۲. روی `Add file` → `Create new file` کلیک کن  
۳. اسم فایل رو بنویس: `README.md`  
۴. کل متن بالا رو اونجا پیست کن  
۵. پایین صفحه روی `Commit new file` بزن

تموم!  
الان READMEت ۱۰۰٪ حرفه‌ای و زیباست و همه عکس‌ها هم وقتی بعداً آپلود کنی خودشون نمایش داده می‌شن.

### فقط یادت باشه بعداً این پوشه رو بساز و عکس‌ها رو بنداز توش:
```
docs/
├── architecture.png
├── tree.png
├── docker-ps.png
├── prom-targets.png
├── grafana-fintech.png
├── grafana-logs.png
├── telegram.png
└── ...
```

اگه خواستی همین الان repo رو برام بفرست، من ست میدم!  
موفق باشی داداش آذری!
