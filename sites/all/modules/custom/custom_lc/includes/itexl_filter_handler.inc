<?php
/* $Id$ */

/**
 * Extend views date handler filter.
 */
class itexl_filter_handler extends views_handler_filter_string {
  /**
   * Shortcut to display the exposed options form.
   */
//    function value_form(&$form, &$form_state) {
//    $form['value'] = array(
//        '#type' => 'select',
//        '#title' => t('State'),
//        '#options' => array(
//            'ACT' => t('ACT'),
//            'NSW' => t('NSW'),
//            'NT' => t('NT'),
//            'QLD' => t('QLD'),
//            'SA' => t('SA'),
//            'TAS' => t('TAS'),
//            'VIC' => t('VIC'),
//            'WA' => t('WA'),
//        ),
//    );
//    return $form;
//    }
    function operators() {
        $operators = parent::operators();
        $operators['user_rated'] = array(
            'title' => t('User Rated Dishes'),
            'short' => t('URD'),
//            'values' => 2,
        );
      
    return $operators;
  }
    function query() {
        switch ($this->operator) {
            case 'user_rated':
                global $user;
                $sql = "votingapi_vote_node_vote.uid = {$user -> uid}";
                $this->query->add_where('', "($sql)");
            break;
       }
    }
}

//class date_extended_filter_handler extends date_api_filter_handler {
// 
//function operators() {
//  $operators = parent::operators();
//    $operators['intime'] = array(
//        'title' => t('In time'),
//        'short' => t('ins'),
//        'values' => 2,
//      );
//      
//    return $operators;
//  }
//  
//  
//  /**
//   * Custom implementation of query() so we can get the
//   * AND and OR methods in the right places.
//   */ 
//  function query() {
//    switch ($this->operator) {
//      case 'intime':
//        $this->get_query_fields();
//        if (!empty($this->query_fields)) {
//          $sql_parts = array();
//          $sql = array(); 
//          
//          // filter have min and max value
//          if ($this->value['min'] && $this->value['max']) {  
//            //filter 1
//            $sql_parts[0][] = $this->date_filter('min', $this->query_fields[0], '>=');
//            $sql_parts[0][] = $this->date_filter('max', $this->query_fields[0], '<=');
//            $sql[] = implode(' AND ' , array_filter($sql_parts[0]));
//            
//            //filter 2
//            $sql_parts[1][] = $this->date_filter('min', $this->query_fields[1], '>=');
//            $sql_parts[1][] = $this->date_filter('max', $this->query_fields[1], '<=');
//            $sql[] = implode(' AND ' , array_filter($sql_parts[1]));
//            
//            //filter 3
//            $sql_parts[2][] = $this->date_filter_extended('min', $this->query_fields[0], '<');
//            $sql_parts[2][] = $this->date_filter_extended('max', $this->query_fields[1], '>');
//            $sql[] = implode(' AND ' , array_filter($sql_parts[2]));
//          }
//          elseif ($this->value['max']) {
//            // filter have only max value
//            $sql[] = $this->date_filter('max', $this->query_fields[0], '<=');
//          }
//          elseif ($this->value['min']) {
//            // filter have only min value
//            $sql[] = $this->date_filter('min', $this->query_fields[1], '>=');
//          }
//          
//          if (!empty($sql[0])) {
//            $this->query->set_where_group('OR', 'date_intime');
//            foreach($sql as $where) {
//              $this->query->add_where('date_intime', $where);
//            }
//            
//          }
//        }
//        break;
//
//      default:
//        parent::query();
//        break;
//    }  
//  }
//  
//  
//  function date_filter_extended($prefix, $query_field, $operator) {
//    $field = $query_field['field'];
//
//    // Views treats the default values as though they are submitted
//    // so we when it is really not submitted we have to adjust the
//    // query to match what should have been the default.
//    $value_parts = !is_array($this->value[$prefix]) ? array($this->value[$prefix]) : $this->value[$prefix];
//    foreach ($value_parts as $part) {
//      $default = $this->default_value($prefix);
//      if (!empty($this->force_value) && !empty($default)) {
//        $this->value[$prefix] = $default;
//      }
//      else {
//        if (empty($part)) {
//          return '';
//        }
//      }
//    }
//    
//    $this->add_date_field($field);
//    $granularity = $this->options['granularity'];
//    $date_handler = $query_field['date_handler'];
//    $this->format = $date_handler->views_formats($granularity, 'sql');
//    $complete_date = date_fuzzy_datetime($this->value[$prefix]);
//    $date = date_make_date($complete_date);
//    $value = date_format($date, $this->format);
//    
//    $range = $this->date_handler->arg_range($value);
//    $year_range = date_range_years($this->options['year_range']);
//    
//    $min_date = $range[0];
//    $max_date = $range[1];
//        
//    $this->min_date = $min_date;
//    $this->max_date = $max_date;
//    $this->year = date_format($date, 'Y');
//    $this->month = date_format($date, 'n');
//    $this->day = date_format($date, 'j');
//    $this->week = date_week(date_format($date, DATE_FORMAT_DATE));
//    $this->date_handler = $date_handler;
//        
//    if ($this->date_handler->granularity == 'week') {
//      $this->format = DATE_FORMAT_DATETIME;
//    }
//    switch ($prefix) {
//      case 'min':
//        $value = date_format($min_date, $this->format);
//        break;
//      case 'max':
//        $value = date_format($max_date, $this->format);
//        break;
//      default:
//        $value = date_format($date, $this->format);
//        break;
//    }
//    if ($this->date_handler->granularity != 'week') {
//      $sql = $date_handler->sql_where_format($this->format, $field['fullname'], $operator, $value);
//    }
//    else {
//      $sql = $date_handler->sql_where_date('DATE', $field['fullname'], $operator, $value);
//    }
//    return $sql;
//  }
//  
//  
//}