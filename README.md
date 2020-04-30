# connmap
connmap is an X11 desktop widget that shows location of your current network peers on a world map.

<p align="center"> 
  <img src="https://raw.githubusercontent.com/jafarlihi/connmap/master/sample.png?token=AKL72SZ6ZUB4HTXII7GKNWK6PYZPA">
</p>

Here's how it looks on my 1366x768 desktop with the default settings:
![desktop](https://raw.githubusercontent.com/jafarlihi/connmap/master/desktop.png?token=AKL72S5HJ6HPGP5PRTAG66K6PYZTG)

## Installation
Clone the repository `git clone https://github.com/jafarlihi/connmap --depth 1` and run `make install`.

## Dependencies
Build dependencies: xlib, libcairo2

Runtime dependencies: `ss` utility of `iproute2` package

## Config
Installation will create `~/.config/connmap/connmaprc`. Default `connmaprc` looks like this:
```
location_x 20
location_y 500
small true
update_interval 1
```
- `location_x`/`location_y` specifies the widget location in your desktop.

- Setting `small` to false will resize widget from 500px/250px to 1000px/500px.

- `update_interval` is seconds the application will sleep for before fetching the updated list of network connections.
## Limitations
- Tested only with i3wm, might not work as expected in other DE/WM.

- Only IPv4 is supported.

- Only country geolocation is supported. Longitude/latitude geolocation might be added in the future.
## IP Database
You can acquire up-to-date IP database from: https://lite.ip2location.com/database/ip-country

It is expected to be found at `$HOME/.config/connmap/resources/IP2LOCATION-LITE-DB1.CSV`

IP database license: https://creativecommons.org/licenses/by-sa/4.0/
