# Gamacon
A ECS C-modular game engine with a builtin renderer using the csfml.

## Samples:
You can find two examples games created using this engine.

A simple 2D plateformer with good physics: [Twac](https://github.com/AnonymusRaccoon/Twac)

An isometric RPG: [ForecastingVillage](https://github.com/AnonymusRaccoon/ForecastingVillage)

## Deserialization & Modularity

Gamacon has a fully xml based deserialization system. Every entity, scene and component can be deserialized from a prefab xml file.

Scene should contains data at the top of the prefab file inside a <data> tag. Each entry will be loaded using one of the registered data_loader. You can create your own data_loader and register them using the ``engine->add_dataloader(engine, data_name, data_loader_fct)`` function.

Gamacon also has a UI handler to ease development of graphical interfaces. For example, you can use a <button> tag with properties like x, y, width or height that handle pixel based or screen's percentage based properties. You also have a click property which will automatically handle your click input.


To look at a read usage of prefabs or scene, take a look at [ForecastingVillage](https://github.com/AnonymusRaccoon/ForecastingVillage) which is the more complete project you can find created with this library.

## Build
To build the library, simple run ``make``.

## Dependencies

Gamacon needs four others libraries:
 - [xmlParser](https://github.com/AnonymusRaccoon/xmlParser) to support a simple deserialization.
 - [Quadtree](https://github.com/AnonymusRaccoon/Quadtree) to handle collisions
 - [CSFML](https://www.sfml-dev.org/download/csfml/) to handle the display. Note that you can use another library to render your scenes but the default makefile rule will require you to have the csfml.
 - libMy a replacement to the libC since we were not allowed to use the standard library durring projects where this game engine was used.
 
