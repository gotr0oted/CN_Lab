# Practical 6: DNS Utilities and Traceroute

## Aim
Inspect DNS records, test reachability, and observe the network route to a destination.

## Suggested exercises
DNS answers and paths vary by network and time. Run these commands yourself.

```sh
nslookup example.com
nslookup -type=NS example.com
nslookup -type=MX gmail.com
ping -c 4 example.com
traceroute example.com
```
With `dig`, try `dig example.com A`, `dig example.com AAAA`, and `dig -x 8.8.8.8`. On Windows, use `ping -n 4 example.com` and `tracert example.com`.

## Record and result
For each command, note its purpose, response type, and one observation from your run. A timeout or filtered hop is a valid observation; do not substitute guessed results. Include your own terminal captures if required.

## Screenshots

### 01 nslookup forward

![Practical 6 - 01 nslookup forward](screenshots/01_nslookup_forward.png)

### 02 ping connectivity

![Practical 6 - 02 ping connectivity](screenshots/02_ping_connectivity.png)

### 03 nslookup ns records

![Practical 6 - 03 nslookup ns records](screenshots/03_nslookup_ns_records.png)

### 04 nslookup cname

![Practical 6 - 04 nslookup cname](screenshots/04_nslookup_cname.png)

### 05 nslookup soa

![Practical 6 - 05 nslookup soa](screenshots/05_nslookup_soa.png)

### 06 nslookup debug

![Practical 6 - 06 nslookup debug](screenshots/06_nslookup_debug.png)

### 07 ipconfig

![Practical 6 - 07 ipconfig](screenshots/07_ipconfig.png)

### 08 nslookup mx

![Practical 6 - 08 nslookup mx](screenshots/08_nslookup_mx.png)

### 09 nslookup reverse

![Practical 6 - 09 nslookup reverse](screenshots/09_nslookup_reverse.png)

### 10 tracert

![Practical 6 - 10 tracert](screenshots/10_tracert.png)

### exp06

![Practical 6 - exp06](screenshots/exp06.png)
