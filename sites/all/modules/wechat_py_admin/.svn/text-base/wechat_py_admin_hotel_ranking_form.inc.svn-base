<?php
/** 
 * hotel ranking form
 */
function menu_wechat_hotel_ranking_form($form, &$form_state){
  // Identify that the elements in 'example_items' are a collection, to
  // prevent Form API from flattening the array when submitted.
  $form['ranking_items']['#tree'] = TRUE;

  if (db_table_exists('wechat_hotel_ranking')){
    $query = db_select('wechat_hotel_ranking', 't');
    $query->fields('t', array('id','hotel_name', 'ranking', 'hotel_longitude', 'hotel_latitude'));

    // Don't forget to tell the query object how to find the header information.
    $result = $query->orderBy('ranking', 'ASC')->execute();

    foreach ($result as $item) {
      $form['ranking_items'][$item->id] = array(
        // set hotel name to display item
        'hotel_name' => array(
          '#markup' => check_plain(t($item->hotel_name)),
        ),

        // We'll use a form element of type '#textfield' to display the item
        // description, which will allow the value to be changed via the form.
        // We limit the input to 255 characters, which is the limit we set on
        // the database field.
        'ranking' => array(
          '#type' => 'textfield',
          '#default_value' => check_plain($item->ranking),
          '#size' => 2,
          '#maxlength' => 2,
        ),
        'hotel_longitude' => array(
          '#type' => 'textfield',
          '#default_value' => check_plain($item->hotel_longitude),
          '#size' => 15,
          '#maxlength' => 15,
        ),
        'hotel_latitude' => array(
          '#type' => 'textfield',
          '#default_value' => check_plain($item->hotel_latitude),
          '#size' => 15,
          '#maxlength' => 15,
        ),

      );
    }
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('保存'));
  return $form;
}

/**
 * Submit callback for the wechat_table_hotel_ranking_form form.
 *
 */
function menu_wechat_hotel_ranking_form_submit($form, &$form_state) {
  // Because the form elements were keyed with the item ids from the database,
  // we can simply iterate through the submitted values.
  //dpm($form_state);
  foreach ($form_state['values']['ranking_items'] as $id => $item) {
    db_update('wechat_hotel_ranking')
    ->fields(array(
        'ranking' => $item['ranking'],
        'hotel_longitude' => $item['hotel_longitude'],
        'hotel_latitude' => $item['hotel_latitude'],
      ))
    ->condition('id', $id)
    ->execute();
  }
}

/**
 * Theme template for hotel ranking form
 */
function theme_menu_wechat_hotel_ranking_form($variables){
  $form = $variables['form'];
  // Initialize the variable which will store our table rows.
  $rows = array();

  foreach (element_children($form['ranking_items']) as $id) {

    // We are now ready to add each element of our $form data to the $rows
    // array, so that they end up as individual table cells when rendered
    // in the final table.  We run each element through the drupal_render()
    // function to generate the final html markup for that element.
    $rows[] = array(
      'data' => array(
        // Add our 'name' column.
        drupal_render($form['ranking_items'][$id]['hotel_name']),
        // Add our 'description' column.
        drupal_render($form['ranking_items'][$id]['ranking']),
        // add hotel_latitude and hotel_longitude column
        drupal_render($form['ranking_items'][$id]['hotel_longitude']),
        drupal_render($form['ranking_items'][$id]['hotel_latitude']),
      ),
      // To support the tabledrag behaviour, we need to assign each row of the
      // table a class attribute of 'draggable'. This will add the 'draggable'
      // class to the <tr> element for that row when the final table is
      // rendered.
      //'class' => array('draggable'),
    );
  }

  $header = array(t('酒店名称'), t('列表排名'), t('酒店地理位置：经度'), t('酒店地理位置：纬度'));

  $table_id = 'ranking-items-table';

  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    //'attributes' => array('id' => $table_id),
  ));

  $output .= drupal_render_children($form);

  return $output;
}

/**
 * End of wechat_py_admin_hotel_ranking_form.inc file name
 */
