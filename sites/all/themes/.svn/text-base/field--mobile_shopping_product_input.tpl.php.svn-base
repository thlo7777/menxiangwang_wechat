<?php

/**
 * @file field--mobile_shopping_product_input.tpl.php
 * Default template implementation to display the value of a field.
 *
 * This file is not used and is here as a starting point for customization only.
 * @see theme_field()
 *
 * Available variables:
 * - $items: An array of field values. Use render() to output them.
 * - $label: The item label.
 * - $label_hidden: Whether the label display is set to 'hidden'.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - field: The current template type, i.e., "theming hook".
 *   - field-name-[field_name]: The current field name. For example, if the
 *     field name is "field_description" it would result in
 *     "field-name-field-description".
 *   - field-type-[field_type]: The current field type. For example, if the
 *     field type is "text" it would result in "field-type-text".
 *   - field-label-[label_display]: The current label position. For example, if
 *     the label position is "above" it would result in "field-label-above".
 *
 * Other variables:
 * - $element['#object']: The entity to which the field is attached.
 * - $element['#view_mode']: View mode, e.g. 'full', 'teaser'...
 * - $element['#field_name']: The field name.
 * - $element['#field_type']: The field type.
 * - $element['#field_language']: The field language.
 * - $element['#field_translatable']: Whether the field is translatable or not.
 * - $element['#label_display']: Position of label display, inline, above, or
 *   hidden.
 * - $field_name_css: The css-compatible field name.
 * - $field_type_css: The css-compatible field type.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess_field()
 * @see theme_field()
 *
 * @ingroup themeable
 */

  $product_imgs['pimg_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('商品属性'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('container-inline')),
  );

  $product_skus['psku_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('商品属性'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
?>
<!--
THIS FILE IS NOT USED AND IS HERE AS A STARTING POINT FOR CUSTOMIZATION ONLY.
See http://api.drupal.org/api/function/theme_field/7 for details.
After copying this file to your theme's folder and customizing it, remove this
HTML comment.
-->
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <?php if($element['#field_name'] == 'field_product_imgs'): ?>
    <!--print product images-->
    <?php
      $product_imgs['pimg_fieldset']['#title'] = $label;
      foreach ($items as $delta => $item) {
        $product_imgs['pimg_fieldset'][$delta] = $item;
      }
      print render($product_imgs);
    ?>
  <?php elseif($element['#field_name'] == 'field_product_sku_list'): ?>
    <?php
      $product_skus['psku_fieldset']['#title'] = $label;
      foreach ($items as $delta => $item) {
        $fc_item = &$item['entity']['field_collection_item'];
        foreach ($fc_item as $key => &$field_item) {
          //dpm($field_item);
          $post_free = $field_item['field_product_post_free']['#items'][0]['value'];
          if($post_free == 1) {
            unset($field_item['field_express_template_id']);
          } else {

            $express_id = $field_item['field_express_template_id']['#items'][0]['value'];
            $query = db_select('wechat_py_shopping_merchant_express_template_table', 't')
              ->condition('t.id', $express_id)
              ->fields('t', array('template_name'));
            $result = $query->execute()->fetchAssoc();
            $gdata['field_express_template_id'][0]['#markup'] = $result['template_name'];
          }

        }
        unset($item['links']);
        $product_skus['psku_fieldset'][$delta] = $item;
      }
      print render($product_skus);
    ?>
  <?php else: ?>
  <!--print other field-->
    <?php if (!$label_hidden): ?>
      <div class="field-label"<?php print $title_attributes; ?>><?php print $label ?>:&nbsp;</div>
    <?php endif; ?>
    <div class="field-items"<?php print $content_attributes; ?>>
      <?php foreach ($items as $delta => $item): ?>
        <div class="field-item <?php print $delta % 2 ? 'odd' : 'even'; ?>"<?php print $item_attributes[$delta]; ?>><?php print render($item); ?></div>
      <?php endforeach; ?>
    </div>
  <?php endif; ?>

</div>
