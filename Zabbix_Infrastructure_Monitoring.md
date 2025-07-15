# داکیومنت فنی : Best Practices مانیتورینگ زیرساخت و امنیت با Zabbix


## تجهیزات تحت مانیتورینگ

- ✅ سرورهای HP با ILO
- ✅ مجازی‌سازهای ESXi و vCenter
- ✅ فایروال‌های FortiGate
- ✅ سوییچ‌های Cisco
- ✅ ماشین‌های مجازی (VMs)

---

## سرور HP (ILO )

| آیتم                                | روش مانیتورینگ | ابزار                  |
| --------------------------------------- | --------------------------- | --------------------------- |
| روشن/خاموش بودن            | IPMI                        | Zabbix IPMI Template        |
| دما، فن، پاور                | IPMI / SNMP                 | HP MIB                      |
| مصرف CPU, RAM, Disk                 | Zabbix Agent                | Template OS Linux / Windows |
| وضعیت RAID و هاردها         | SNMP                        | HP Insight Tools            ||

---

## vCenter و ESXi

| آیتم                      | روش مانیتورینگ | ابزار                 |
| ----------------------------- | --------------------------- | -------------------------- |
| وضعیت هاست‌ها     | vSphere API                 | Template VMware            |
| وضعیت VMها             | API                         | Template VMware            |
| استفاده منابع     | API                         | vmware.vm.resource metrics |
| Snapshotهای قدیمی     | Auto-Discovery              | Template VMware            |
| رخدادهای vMotion / HA | Event Polling               | vCenter Alarm              |

---

## FortiGate Firewall

| آیتم                  | روش مانیتورینگ | ابزار              |
| ------------------------- | --------------------------- | ----------------------- |
| CPU و RAM                | SNMP                        | Template SNMP FortiGate |
| Interfaceها             | SNMP + Discovery            | FortiGate IF Metrics    |
| تعداد Sessions       | SNMP                        | fgSysSesCount           |
| وضعیت VPN            | SNMP                        | IPsec/SSL Metrics       |

---

## سوییچ Cisco

| آیتم                  | روش مانیتورینگ | ابزار                 |
| ------------------------- | --------------------------- | -------------------------- |
| وضعیت پورت‌ها | SNMP + LLD                  | ifOperStatus               |
| Errors / CRC              | SNMP                        | Interface Counters         |
| دما                    | SNMP                        | CiscoEnvMon                |
| STP / Routing             | SNMP                        | STP/Routing Tables         |

---

## ماشین‌های مجازی (VMs)

| آیتم                    | روش مانیتورینگ | ابزار                         |
| --------------------------- | --------------------------- | ---------------------------------- |
| روشن بودن           | Ping                        | Zabbix ICMP                        |
| منابع مصرفی       | Zabbix Agent                | Template OS Linux / Windows        |
| وضعیت سرویس‌ها | Agent                       | service.info[,state] |
| فضای دیسک           | Agent + Discovery           | vfs.fs.size[*]                     |

---

# 🛡️ مانیتورینگ امنیتی VMها

## 1. Authentication Monitoring

| آیتم                           | نوع  | کلید / فرمان                                              | توضیح                                    |
| ---------------------------------- | ------- | ------------------------------------------------------------------ | --------------------------------------------- |
| ورود ناموفق SSH          | Log     | `log[/var/log/auth.log, Failed password, UTF-8]`                   | بررسی لاگ ورودهای ناموفق |
| ورود root                      | Log     | `log[/var/log/auth.log, Accepted password for root, UTF-8]`        | مانیتور ورود root                  |
| ورود ناموفق ویندوز | Log     | `logrt["C:\\Windows\\System32\\winevt\\Logs\\Security.evtx",4625]` | لاگ ورود در ویندوز             |
| تلاش‌های زیاد ورود | Trigger | بیش از ۵ بار در ۵ دقیقه                           | تشخیص Brute Force                        |

## 2. System Change Monitoring

| آیتم                    | نوع     | فرمان                                                    | توضیح                        |
| --------------------------- | ---------- | ------------------------------------------------------------- | --------------------------------- |
| تغییر فایل sudoers | Text       | `vfs.file.contents[/etc/sudoers]`                             | تشخیص تغییرات مهم  |
| کاربر جدید         | Log        | `log[/var/log/auth.log, new user]`                            | بررسی اضافه شدن user |
| فایروال فعال؟   | Text       | `system.run[ufw status]` یا `system.run[firewalld --state]` | چک امنیتی                 |

## 3. Network & Firewall Monitoring

| آیتم                   | نوع  | فرمان                                                                                                                  | توضیح                              |
| -------------------------- | ------- | --------------------------------------------------------------------------------------------------------------------------- | --------------------------------------- |
| تعداد پورت باز | Numeric | `system.run[ss -tuln                                                                                                        | wc -l]`                                 |
| پورت SSH               | Net.TCP | `net.tcp.port[22]`                                                                                                          | بسته بودن یا هشدار       |

## 4. Update & Patch

| آیتم                        | نوع  | فرمان                                      | توضیح                    |
| ------------------------------- | ------- | ----------------------------------------------- | ----------------------------- |
| بروزرسانی لینوکس | Numeric | `system.run[apt list --upgradable               | wc -l]`                       |
| آپدیت ویندوز         | Script  | PowerShell Script                               | بررسی بروزرسانی |

## 5. Suspicious Behavior

| آیتم            | نوع     | فرمان                      | توضیح                           |
| ------------------- | ---------- | ------------------------------- | ------------------------------------ |
| uptime              | Uptime     | `system.uptime`                 | تشخیص ریبوت ناگهانی |
| دیسک پر       | Numeric    | `vfs.fs.size[/,pfree]`          | تهدید پرفورمنس          |
| زمان سیستم | Text       | `system.run[ntpq -pn            | head -n 10]`                         |

---


