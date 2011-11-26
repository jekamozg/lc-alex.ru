<?php

/**
* Implementation of hook_views_handlers().
*/
function itexl_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'itexl') .'/includes',
    ),
    'handlers' => array(
      'itexl_filter_handler' => array(
        'parent' => 'views_handler_filter_string',
      ),

    ),
  );
}

function itexl_views_data() {
 
$data = array(); 
$data['node']['itexl'] = array(
  'title' => t('itexl'),
  'help' => t('Filter by user rating.'),
  'real field' => 'title',
//  'group' => t('Location state'),
  'filter' => array(
    'handler' => 'itexl_filter_handler',
  ),
);
return $data;
}

//function itexl_views_data_alter(&$data) {
//    
//    $data['location']['distance']['filter']['handler'] = 'city_search_views_handler_filter_proximity';
//
//}

/**
 * Implementation of hook_views_data()
 */
//function date_extended_views_data_alter(&$data) {
//  
//  $tables = module_invoke_all('date_api_tables');
//  
//  foreach ($tables as $base_table) { 
//    
//    $data[$base_table]['date_filter']['filter']['handler'] = 'date_extended_filter_handler';
//
//  }
//
//}