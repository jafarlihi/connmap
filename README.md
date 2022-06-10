# connmap
connmap is an X11 desktop widget that shows location of your current network peers on a world map.

<p align="center"> 
  <img src="https://raw.githubusercontent.com/jafarlihi/connmap/master/sample.png?token=AKL72SZ6ZUB4HTXII7GKNWK6PYZPA">
</p>

## Installation
Clone the repository `git clone https://github.com/jafarlihi/connmap --depth 1`, run `make install`, then run the resulting executable `./connmap.exe`.

## Dependencies
Build dependencies: xlib, libcairo2

Runtime dependencies: `ss` utility of `iproute2` package

## Config
Installation will create `~/.config/connmap/connmaprc`. Default `connmaprc` looks like this:
```
location_x 20
location_y 500
small true
black false
update_interval 1
```
- `location_x`/`location_y` specifies the widget location in your desktop.

- Setting `small` to false will resize widget from 500px/250px to 1000px/500px.

- Setting `black` to true will draw map outline in black instead of white.

- `update_interval` is seconds the application will sleep for before fetching the updated list of network connections.
## Limitations
- Tested only with i3wm, might not work as expected in other DE/WM.

- Only IPv4 is supported.
