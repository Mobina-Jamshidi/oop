
# 📘 داکیومنت فنی و تخصصی: Best Practices مانیتورینگ زیرساخت و امنیت با Zabbix

این سند یک راهنمای حرفه‌ای برای تیم‌های DevOps، NetOps، SysAdmin و InfoSec است تا بتوانند زیرساخت ترکیبی خود را با ابزار متن‌باز Zabbix به‌شکلی موثر و ایمن مانیتور کنند. 
سند شامل مانیتورینگ تجهیزات فیزیکی، مجازی، امنیت شبکه و تحلیل رفتار مشکوک در سطح VM می‌باشد.

---

## 🧩 تجهیزات تحت مانیتورینگ

- ✅ سرورهای HP با ILO
- ✅ مجازی‌سازهای ESXi و vCenter
- ✅ فایروال‌های FortiGate
- ✅ سوییچ‌های Cisco
- ✅ ماشین‌های مجازی (VMs)
- ✅ لاگ‌ها، منابع، امنیت و سرویس‌ها

---

## 🖥️ سرور HP (ILO + OS)

| آیتم | روش مانیتورینگ | ابزار |
|------|------------------|-------|
| روشن/خاموش بودن | IPMI | Zabbix IPMI Template |
| دما، فن، پاور | IPMI / SNMP | HP MIB |
| مصرف CPU, RAM, Disk | Zabbix Agent | Template OS Linux / Windows |
| وضعیت RAID و هاردها | SNMP | HP Insight Tools |
| لاگ‌های سخت‌افزاری IML | Agent + log | /var/log/ilo.log |

---

## 🖧 vCenter و ESXi

| آیتم | روش مانیتورینگ | ابزار |
|------|------------------|-------|
| وضعیت هاست‌ها | vSphere API | Template VMware |
| وضعیت VMها | API | Template VMware |
| استفاده منابع | API | vmware.vm.resource metrics |
| Snapshotهای قدیمی | Auto-Discovery | Template VMware |
| رخدادهای vMotion / HA | Event Polling | vCenter Alarm |

---

## 🔥 FortiGate Firewall

| آیتم | روش مانیتورینگ | ابزار |
|------|------------------|-------|
| CPU و RAM | SNMP | Template SNMP FortiGate |
| Interfaceها | SNMP + Discovery | FortiGate IF Metrics |
| تعداد Sessions | SNMP | fgSysSesCount |
| وضعیت VPN | SNMP | IPsec/SSL Metrics |
| لاگ‌های UTM و IPS | Syslog یا SNMP | Log Server / ELK |

---

## 🌐 سوییچ Cisco

| آیتم | روش مانیتورینگ | ابزار |
|------|------------------|-------|
| وضعیت پورت‌ها | SNMP + LLD | ifOperStatus |
| Errors / CRC | SNMP | Interface Counters |
| دما | SNMP | CiscoEnvMon |
| STP / Routing | SNMP | STP/Routing Tables |
| Syslog تغییرات | Syslog | به Zabbix Proxy یا ELK |

---

## 💻 ماشین‌های مجازی (VMs)

| آیتم | روش مانیتورینگ | ابزار |
|------|------------------|-------|
| روشن بودن | Ping | Zabbix ICMP |
| منابع مصرفی | Zabbix Agent | Template OS Linux / Windows |
| وضعیت سرویس‌ها | Agent | service.info[<service_name>,state] |
| فضای دیسک | Agent + Discovery | vfs.fs.size[*] |
| لاگ‌ها | Agent log[] | Syslog / Windows Log |

---

# 🛡️ مانیتورینگ امنیتی VMها

## 1. Authentication Monitoring

| آیتم | نوع | کلید / فرمان | توضیح |
|------|------|---------------|--------|
| ورود ناموفق SSH | Log | `log[/var/log/auth.log, Failed password, UTF-8]` | بررسی لاگ ورودهای ناموفق |
| ورود root | Log | `log[/var/log/auth.log, Accepted password for root, UTF-8]` | مانیتور ورود root |
| ورود ناموفق ویندوز | Log | `logrt["C:\\Windows\\System32\\winevt\\Logs\\Security.evtx",4625]` | لاگ ورود در ویندوز |
| تلاش‌های زیاد ورود | Trigger | بیش از ۵ بار در ۵ دقیقه | تشخیص Brute Force |

## 2. System Change Monitoring

| آیتم | نوع | فرمان | توضیح |
|------|------|--------|--------|
| تغییر فایل sudoers | Text | `vfs.file.contents[/etc/sudoers]` | تشخیص تغییرات مهم |
| کاربر جدید | Log | `log[/var/log/auth.log, new user]` | بررسی اضافه شدن user |
| فایروال فعال؟ | Text | `system.run[ufw status]` یا `system.run[firewalld --state]` | چک امنیتی |
| سرویس جدید | System.run | `system.run[systemctl list-units --type=service]` | تشخیص موارد مشکوک |

## 3. Network & Firewall Monitoring

| آیتم | نوع | فرمان | توضیح |
|------|------|--------|--------|
| تعداد پورت باز | Numeric | `system.run[ss -tuln | wc -l]` | چک پورت‌های مشکوک |
| پورت SSH | Net.TCP | `net.tcp.port[22]` | بسته بودن یا هشدار |
| IPهای مشکوک | Log | تحلیل لاگ فایروال یا IDS | ارتباط خطرناک |
| VPN | TCP | بررسی وضعیت اتصال VPN (مانند پینگ گیت‌وی داخلی یا مانیتور لاگ OpenVPN/IPsec) | اطمینان از ترافیک امن |

## 4. Update & Patch

| آیتم | نوع | فرمان | توضیح |
|------|------|--------|--------|
| بروزرسانی لینوکس | Numeric | `system.run[apt list --upgradable | wc -l]` | آپدیت‌های معوق |
| آنتی‌ویروس فعال؟ | Text | `system.run[systemctl is-active clamav-daemon]` | سلامت امنیتی |
| آپدیت ویندوز | Script | PowerShell Script | بررسی بروزرسانی |

## 5. Suspicious Behavior

| آیتم | نوع | فرمان | توضیح |
|------|------|--------|--------|
| CPU مشکوک | System.run | `system.run[ps aux --sort=-%cpu | head -n 5]` | تشخیص miner یا باج‌افزار |
| uptime | Uptime | `system.uptime` | تشخیص ریبوت ناگهانی |
| دیسک پر | Numeric | `vfs.fs.size[/,pfree]` | تهدید پرفورمنس |
| زمان سیستم | Text | `system.run[ntpq -pn | head -n 10]` | جلوگیری از اختلاف زمانی |

---

## ✅ خلاصه

- مانیتورینگ auth + لاگ‌های امنیتی
- بررسی منابع مصرفی غیرعادی و تغییرات سیستمی
- نظارت روی باز بودن پورت‌ها و ارتباطات مشکوک
- بررسی وضعیت بروزرسانی سیستم و سلامت AV

---

## 📌 نویسنده: تیم فنی زیرساخت  
**ابزار اصلی:** Zabbix 6.x+, Agent2, SNMPv3, IPMI, Syslog, Custom Scripts  
**وضعیت:** قابل ارائه برای استفاده در سازمان‌ها و مراکز داده
