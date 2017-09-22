<?php
class wechat_py_shopping_views_handler_field_area_id extends views_handler_field {

  function render($values) {

    $value = $this->get_value($values);
    $term = taxonomy_term_load($value);
    $area = $term->name;
    return $area;

  }

}

