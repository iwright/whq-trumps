<?php
/*
 * Add post thumbnail support.
 */
if (function_exists('add_theme_support')) {
  // Register custom image sizes.
  add_image_size('whq_trumps_card', 500, 320, ['center', 'center'] );
}
