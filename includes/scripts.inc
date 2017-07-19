<?php
/**
 * Enqueue Styles and Scripts for displaying and interactions.
 */
function whq_trumps_card_scripts() {
  // Load in our JS file which will control the card sorting.
  // Include a dependency on jQuery provided by core.
  wp_enqueue_script('whq-trumps-script',
    plugins_url('assets/js/whq-trumps.js', dirname(__FILE__)),
    ['jquery']
  );

  // Register our AJAX POST parameters.
  $whq_trumps_card_request_nonce = wp_create_nonce('whq_trumps_card_request');
  wp_localize_script( 'whq-trumps-script', 'whq_trumps_ajax', [
    'ajax_url' => admin_url('admin-ajax.php'),
    'nonce' => $whq_trumps_card_request_nonce,
  ]);
}
add_action('wp_enqueue_scripts', 'whq_trumps_card_scripts');
