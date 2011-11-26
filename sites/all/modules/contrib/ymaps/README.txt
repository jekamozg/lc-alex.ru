
YMaps drupal module.

This module implements basic drupal site interaction with the Yandex Maps API.


Installation.
1. Put module directory to your /sites/all/modules/ directory;
2. Enable module on the admin's "Modules" page;
3. Enter valid API-key for the current site on the YMaps settings page.

Usage.
You may create one YMaps block and set up it features.
With Multiblock module you may create as many instances with different settings as you wish.
Now module shows locations for the current node and its "children" nodes (added through nodereference module).
Also module implements basic geocoding on client side for location-edit forms.
You may use a views with the "ymaps" output style to show node locations.
With the taxonomy image module it is possible to show images on the maps except standard placemarks.
With the track module You may draw, store and show tracks on the maps.