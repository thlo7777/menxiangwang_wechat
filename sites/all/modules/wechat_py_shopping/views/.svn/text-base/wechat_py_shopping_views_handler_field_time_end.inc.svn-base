<?php
class wechat_py_shopping_views_handler_field_time_end extends views_handler_field {

  function render($values) {
    $value = $this->get_value($values);

    $time = strtotime($value);
    $time_end = date('Y年m月d日 H:i',$time);

    return $time_end;

  }

}



