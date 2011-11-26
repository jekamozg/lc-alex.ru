<?php
  
     /**
     *
     * @ingroup views_style_plugins
     */
class ymaps_plugin_style_ymaps extends views_plugin_style {
function option_definition() {
  $options = parent::option_definition();
     
   $options['trackcolor'] = array('default' => 'ff0000');
   $options['trackshow'] = array('default' => TRUE);
   $options['trackwidth'] = array('default' => 2);
   $options['zoom'] = array('default' => TRUE);
   $options['typecontrol'] = array('default' => TRUE);

  return $options;
}



function options_form(&$form, &$form_state) {

  $form['zoom'] = array(
  '#type' => 'checkbox',
  '#title' => t('Zoom control'),
  '#default_value' =>  !empty($this->options['zoom']),
  '#description' => t("Zoom control"),
  );
  $form['toolbar'] = array(
  '#type' => 'checkbox',
  '#title' => t('Add toolbar'),
  '#default_value' => !empty($this->options['toolbar']),
  '#description' => t("Add toolbar"),
  );
  $form['typecontrol'] = array(
  '#type' => 'checkbox',
  '#title' => t('Show type control'),
  '#default_value' => !empty($this->options['typecontrol']),
  '#description' => t("Show type control"),
  );
  $form['minimap'] = array(
  '#type' => 'checkbox',
  '#title' => t('Add minimap'),
  '#default_value' => !empty($this->options['minimap']),
  '#description' => t("Add minimap"),
  );
  $form['scaleline'] = array(
  '#type' => 'checkbox',
  '#title' => t('Add scaleline'),
  '#default_value' => !empty($this->options['scaleline']),
  '#description' => t("Add scaleline"),
  );
  $form['showchilds'] = array(
  '#type' => 'checkbox',
  '#title' => t('Show childs node locations '),
  '#default_value' => !empty($this->options['showchilds']),
  '#description' => t("Show locations of the nodereference fields"),
  );
  $form['showteaser'] = array(
  '#type' => 'checkbox',
  '#title' => t('Show teasers in balloons'),
  '#default_value' => !empty($this->options['showteaser']),
  '#description' => t("Show teasers in balloons"),
   );
  $form['trackshow'] = array(
  '#type' => 'checkbox',
  '#title' => t('Show tracks on the map'),
  '#default_value' => !empty($this->options['trackshow']),
  '#description' => t("Show tracks on the map (depends on trackfield module)"),
  );          
  $form['trackwidth'] = array(
  '#type' => 'select', 
  '#title' => t('Width of the track'), 
  '#default_value' => $this->options['trackwidth'],
  '#options' => drupal_map_assoc(array(1,2,3,4,5)), 
  '#description' => t('Width of the track'),
  );
  $form['trackcolor'] = array(
  '#type' => 'textfield', 
  '#title' => t('Stroke color'), 
  '#size' => 8, 
  '#maxlength' => 8,
  '#default_value' => $this->options['trackcolor'],
  '#description' => t('Stroke color, RGBA in hex format'),
  );

 }

function render() {
  ymaps_doheader();
  $rows = array();

  $ov = array('placemarks' =>array(), 'tracks' => array(),);
  foreach ($this->view->result as $row) {
//   if (!empty($row->node_nid)) {
//   $curov = ymaps_get_map_overlays($row->node_nid);
//   $ov['placemarks'] = array_merge($ov['placemarks'],(array)$curov['placemarks']);
//   $ov['tracks'] = array_merge($ov['tracks'],(array)$curov['tracks']);
//   }
  if (!empty($row->nid)) {
    $curov = ymaps_get_map_overlays($row->nid,FALSE,$this->options['trackshow']);
    $ov['placemarks'] = array_merge($ov['placemarks'],(array)$curov['placemarks']);
    $ov['tracks'] = array_merge($ov['tracks'],(array)$curov['tracks']);
  }
}

  $mapid = 'view' . $this->view->name . $this->view->vid;
  $mapcode = "$(document).ready(function(){ YMaps.load(ymapsinit('$mapid'));
  " ._ymaps_map_settings($mapid,(array)$this->options)." 
  " . ymaps_tracks_show($mapid, $ov['tracks']) . " " .ymaps_markers_show($mapid,$ov['placemarks'])." }); ";


  drupal_add_js($mapcode , 'inline', 'header', FALSE, FALSE, FALSE);


//print_r($this->view->result);
  return theme($this->theme_functions(), $this->view, $this->options, $rows);
}
}

