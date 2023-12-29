# remote practical experiences

## Backgrand
- if the user didn't have an acount there is a request in witch the user can send a submition request
- send email (not implemented yet)

### Data
~~~bash
CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    username TEXT NOT NULL,
    hash TEXT NOT NULL);

CREATE UNIQUE INDEX username ON users (username);


CREATE TABLE IF NOT EXISTS users_information (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    first_name TEXT NOT NULL,
    last_name TEXT NOT NULL,
    email TEXT NOT NULL,
    establishment TEXT NOT NULL,
    sector TEXT NOT NULL,
    phone TEXT NOT NULL,
    contry TEXT NOT NULL);

CREATE TABLE IF NOT EXISTS temperature (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    temperature NUMERIC,
    humidity NUMERIC,
    date DATETIME NOT NULL);

CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    a NUMERIC,
    b NUMERIC);
~~~

## Setting up the Raspberry Pi
- [Installing Raspberry Pi OS](https://www.raspberrypi.com/software/)
- [Set a Static IP Address on Raspberry Pi](https://www.tomshardware.com/how-to/static-ip-raspberry-pi)
    ~~~bash
    nano /etc/dhcpcd.conf

    #profile static_eth0
    static ip_address=
    static routers=
    static domain_name_servers=
    static domain_search=
    ~~~

- update the Raspberry Pi
    ~~~bash
    sudo apt update
    sudo apt upgradde
    sudo date -s "11 Nov 2023 11:00:00"
    ~~~

##	Setting up a web page for room monitoring

- create a table of temperature values in MySQL database
    ~~~bash
    CREATE TABLE IF NOT EXISTS temperature (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    temperature NUMERIC,
    humidity NUMERIC,
    date DATETIME NOT NULL);
    ~~~

- Connect Bulbs to control over the web
    Bulbs|Raspberry Pi pin|Relay state
    :---:|:---:|:---:
    bulb1 |physical 15 (GPIO pin 22)|NC (Normally open)
    bulb2 |physical 16 (GPIO pin 23)|NC (Normally open)
    bulb3 |physical 22 (GPIO pin 25)|NO (Normally open)

