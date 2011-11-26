<?php

function imagefield_crop_drush_command() {
  $items = array();

  $items['image-recrop'] = array(
    'description' => "Recrop images in a specific node",
    'arguments' => array('node-id' => 'The node to run recrop on'),
    'drupal dependencies' => array('content', 'imageapi'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );
  return $items;
}

function drush_imagefield_crop_image_recrop($nid) {
  imagefield_crop_recrop($nid);
}

/**
 * Utility function used if you want to recrop all images in a specific node.
 * This might be useful if you want to reprocess your nodes using a different toolkit,
 * or a different toolkit configuration
 */
function imagefield_crop_recrop($nid) {
  $node = node_load($nid);
  foreach (content_fields(NULL, $node->type) as $field)
    if (($field['module'] == 'filefield') && ($field['widget']['type'] == 'imagefield_crop_widget')) {
      if ($field['widget']['resolution']) {
        list($scale['width'], $scale['height']) = explode('x', $field['widget']['resolution']);
      }
      if (is_array($node->{$field['field_name']})) {
        foreach ($node->{$field['field_name']} as $image_field) {
          if ($image_field['fid']) {
            // we have an image, recrop it.
            $file = field_file_load($image_field['fid']);
            drush_print("Recropping " . $file['filepath']);
            _imagefield_crop_resize(imagefield_crop_file_admin_original_path($file),
                                    $image_field['data']['crop'],
                                    $scale,
                                    $file['filepath']);
          }
        }
      }
    }
}
