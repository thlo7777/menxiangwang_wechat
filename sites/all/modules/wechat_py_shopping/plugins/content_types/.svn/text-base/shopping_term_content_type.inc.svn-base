<?php
/**
 * Create pane by ctools plug in for wechat shopping vocabulary term and category.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,  // Just do this one, it is needed.
  'title' => t('微商城分类规则Pane'),  // Title to show up on the pane screen.
  'content_types' => 'shopping_term_content_type',
  'description' => t('显示微商城分类规则，只显示相应分类下的节点内容'), // Description to show up on the pane screen.
  'category' => t('微商城分类Pane'), // A category to put this under.
  //'edit form' => 'shopping_pane_custom_pane_edit_form', // A function that will return the settings form for the pane.
  'render callback' => 'shopping_pane_custom_pane_render', // A function that will return the renderable content.
  'admin title' => 'shopping_pane_custom_pane_admin_title',
  'admin info' => 'shopping_pane_custom_pane_admin_info', // A function that will return the information displayed on the admin screen (optional).
  'all contexts' => TRUE, // This is NEEDED to be able to use substitution strings in your pane.
);

/**
 * 'edit form' callback for the content type.
 */
function shopping_pane_custom_pane_edit_form($form, &$form_state) {
  $form['text'] = array(
    '#markup' => '<div>shopping term pane</div>',
  );

  $form['desc'] = array(
    '#type' => 'textfield',
    '#title' => t('my first Text'),
    '#description' => t('Text to display, it may use substitution strings'),
    '#default_value' => 'hello',
  );
  return $form;
}

/**
 * Run-time rendering of the body of the block (content type)
 *
 * @param $subtype
 * @param $conf
 *   Configuration as done at admin time
 * @param $args
 * @param $context
 *   Context - in this case we don't have any
 *
 * @return
 *   An object with at least title and content members
 */
function shopping_pane_custom_pane_render($subtype, $conf, $args, $context) {

  $block = new stdClass();

  // initial content is blank
  $block->title = t('shopping term content type!'); // This will be overridden by the user within the panel options.

  $render_array = array(
    '#type' => 'textfield',
    '#title' => t('my render first Text'),
    '#description' => t('Text to display, it may use substitution strings'),
    '#default_value' => 'hello',
  );

  $element['text'] = array(
    '#markup' => drupal_render($render_array),
    '#prefix' => '<div>',
    '#suffix' => '</div>',
  );

  $block->content = drupal_render($element);  
  return $block;
}

/**
 * Callback to provide administrative info (the preview in panels when building
 * a panel).
 *
 * In this case we'll render the content with a dummy argument and
 * a dummy context.
 */
function shopping_pane_custom_pane_admin_info($subtype, $conf, $context = NULL) {
  $block = new stdClass();
  $block->title = t('显示微商城分类规则，只显示相应分类下的节点内容');
  return $block;
}

function shopping_pane_custom_pane_admin_title($subtype, $conf, $context = NULL) {
  $output = t('shopping pane!!!!');
  return $output;
}
