# Part 3 - Black Hat Bash Lab

## 3.A - Lab architecture

| Machine       | Public IP (172.16.10.0/24) | Corporate IP (10.1.0.0/24) | Hostname      |
|---------------|------------------------------|-------------------------------|---------------|
| p-web-01      | 172.16.10.10                  | -                              | p-web-01      |
| p-ftp-01      | 172.16.10.11                  | -                              | p-ftp-01      |
| p-web-02      | 172.16.10.12                  | 10.1.0.11                      | p-web-02      |
| p-jumpbox-01  | 172.16.10.13                  | 10.1.0.12                      | p-jumpbox-01  |
| c-backup-01   | -                              | 10.1.0.13                      | c-backup-01   |
| c-redis-01    | -                              | 10.1.0.14                      | c-redis-01    |
| c-db-01       | -                              | 10.1.0.15                      | c-db-01       |
| c-db-02       | -                              | 10.1.0.16                      | c-db-02       |

Nota: p-web-02 y p-jumpbox-01 tienen interfaces en ambas redes - actuan como puente entre la zona publica y la corporativa. Esto permite que un atacante que comprometa una maquina publica con doble interfaz pueda pivotar hacia la red corporativa interna.

## Network diagram

Public network (172.16.10.0/24, br_public, gw 172.16.10.1):
  p-web-01      .10
  p-ftp-01      .11
  p-web-02      .12  --- bridge ---
  p-jumpbox-01  .13  --- bridge ---

Corporate network (10.1.0.0/24, br_corporate, gw 10.1.0.1):
  p-web-02      .11  (bridge from public)
  p-jumpbox-01  .12  (bridge from public)
  c-backup-01   .13
  c-redis-01    .14
  c-db-01       .15
  c-db-02       .16

## Evidence

- make deploy completed successfully.
- make test result: Lab is up.
- docker ps confirms 8 containers running: p-web-01, p-ftp-01, p-web-02, p-jumpbox-01, c-backup-01, c-redis-01, c-db-01, c-db-02.
- ip addr | grep br_ confirms br_public (172.16.10.1/24) and br_corporate (10.1.0.1/24).
- Access demonstrated via sudo docker exec -it p-web-01 bash, whoami = root, hostname = p-web-01.acme-infinity-servers.com

## 3.B - Hacking technique: web stack fingerprinting

Tool: WhatWeb
Target: p-web-01 (172.16.10.10:8081)

Command:
ruby whatweb -v http://172.16.10.10:8081

What it does: WhatWeb sends an HTTP request and analyzes response headers, HTML metadata, and known plugin signatures to identify the technology stack of a web application, without needing credentials or system access.

Why it works: web servers expose identifying information by default in HTTP headers (e.g. Server string) and HTML markup (e.g. doctype). This information is not hidden unless explicitly configured otherwise.

Result: the target runs a Python Flask-style application served via Werkzeug 3.0.1 (Flask's built-in development server) on Python 3.12.3, not behind a production-grade server like Nginx or Apache.

Interpretation: the presence of Werkzeug's dev server in a deployed environment indicates the application was likely never hardened for production. This narrows the attack surface significantly: instead of guessing the technology, we can now search for known CVEs specific to Werkzeug 3.0.1 / Python 3.12.3, and treat the lack of a reverse proxy as a finding in itself. The page title "Menu" also suggests multiple navigable routes, making directory enumeration (dirsearch) a logical next step.
