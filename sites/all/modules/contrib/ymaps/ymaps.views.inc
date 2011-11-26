<?php

/**
 * @file
 * Ymaps views support.
 */

/**
 * Implementation of hook_views_plugins().
 */
function ymaps_views_plugins() {
  return array(
    'style' => array(
       'ymaps' => array(
          'title' => t('YMaps'),
          'help' => t('Displays rows as a Yandex map. <br /> (Accepts node id and shows assosiated locations and tracks)'),
          'handler' => 'ymaps_plugin_style_ymaps',
          'theme' => 'ymaps_view_ymaps',
          'uses fields' => FALSE,
          'uses row plugin' => FALSE,
          'uses options' => TRUE,
          'type' => 'normal',
          ),
       ),
  );
}
