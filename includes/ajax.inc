<?php
/**
 * Define handler for the ajax request.
 */
function whq_trumps_ajax_handler() {
  // Make sure the ajax referral is correct.
  check_ajax_referer('whq_trumps_card_request');

  // Sanitize our POST data.
  $whq_card_deck = sanitize_text_field($_POST['whq_trumps_deck']);
  $whq_trumps_orderby = sanitize_text_field($_POST['whq_trumps_orderby']);

  // Reconstruct the body of the deck with our new POSTed parameters.
  $ordered_deck = whq_trumps_card_body($whq_card_deck,'DESC', $whq_trumps_orderby);

  // Push the reordered/reconstructed card list to the Front-End.
  wp_send_json($ordered_deck);
}

/**
 * wp_ajax_nopriv_(action).
 * wp_ajax_(action).
 *
 * Action: whq_trumps_card_request
 *
 * Make sure our ajax requests can run for authenticated and anonymous users.
 *
 */
add_action('wp_ajax_nopriv_whq_trumps_card_request', 'whq_trumps_ajax_handler');
add_action('wp_ajax_whq_trumps_card_request', 'whq_trumps_ajax_handler');
