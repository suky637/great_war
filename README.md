# Great War
This is the open source part of the project

## Building from source
For that you'll need to install:
- JSON by nlohmann, version 3.11.3
- OpenAL
- SFML, version 2.6.2

**Quick notice**: When the build is sucessful, expect a crash, it is mainly due to the fact that the game is *data driven* so you need the required JSONs to run that game, which is closed-source, but you can make your own.

**Structure of your jsons**:

```
ressources/
|-> game.json
\-> window.json
```

## Game.json

Game.json contains the maps, and the guis, you can define it like that:
```json
{
    "currentWorld": 0,
    "currentGUI": 0,
    "worlds": [
        "ressources/maps/***.json"
    ],
    "guis": [
        "ressources/guis/***.json",
    ]
}
```

## Window.json
```json
{
    "window_name": "***",
    "icon": "ressources/window/***.png",
    "default_width": 1280,
    "default_height": 720
}
```

## Example of a gui.json
```json
{
    "world_map_gui": [
        {
            "type": "FRAME",
            "position": [0, 0],
            "scale": [1280, 60],
            "id": ""
        },
        {
            "type": "BUTTON",
            "position": [10, 10],
            "scale": [100, 100],
            "text": "Click me",
            "id": ""
        },
        {
            "type": "LABEL",
            "position": [300, 0],
            "text": "Super Label",
            "id": "yeah"
        }
    ],
    "world_map_gui_config": {
        "font": "ressources/***.ttf"
    }
}
```

## Example of a map.json
```json
{
    "config": {
        "backgroundColour": {"R": 0, "G": 0, "B": 0, "A": 0}, // A = 255 is opaque
        "backgroundImage": "ressources/***.png",
        "countryOpacity": 255,
        "EDITOR_MODE": false,
        "EDITOR_SNAPPING_ENABLED": false,
        "EDITOR_SNAPPING": 3 // In pixels
    },
    "countries": [
        {
            "name": "***",
            "ISO": "***",
            "flag": "none",
            "colour": {
                "R": 0,
                "G": 0,
                "B": 0
            },
            "regions": [
                {
                    "name": "***_RG1",
                    "text_pos": {"X": 0, "Y": 0},
                    "scale": 1,
                    "coords": [
                        {"X": 0, "Y": 0},
                        {"X": 10, "Y": 0},
                        {"X": 0, "Y": 10},
                    ]
                }
            ]
        }
    ]
}
```