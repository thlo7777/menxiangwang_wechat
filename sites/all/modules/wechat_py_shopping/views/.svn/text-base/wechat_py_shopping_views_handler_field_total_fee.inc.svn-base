<?php
class wechat_py_shopping_views_handler_field_total_fee extends views_handler_field {

  function render($values) {

    $value = $this->get_value($values);

    $total_fee = number_format(floatval($value)/100, 2);
    return $total_fee;

  }

}

