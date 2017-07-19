<?php
/*
  Plugin Name: WHQ Trumps
  Plugin URI: https://wrightshq.com
  Description: A WordPress Plugin for creating and interacting with Top Trumps cards.
  Version: 1.0.0
  Author: Ian Wright
  Author URI: https://wrightshq.com
  License: GPL2
*/

// Includes.
require_once('includes/taxonomy.inc');
require_once('includes/shortcodes.inc');
require_once('includes/scripts.inc');
require_once('includes/ajax.inc');

/**
 * register_activation_hook().
 */
function whq_trumps_activate() {
  // Register a CPT on plugin activation.
  whq_register_trumps_cpt();
  // Register our custom taxonomy (Decks)
  whq_trumps_taxonomy();
  // Register our shortcode.
  whq_trumps_shortcode_init();
  // Include our custom scripts.
  whq_trumps_card_scripts();
  // Ajax request.
  whq_trumps_ajax_handler();
}
register_activation_hook(__FILE__, 'whq_trumps_activate');

/**
 * register_post_type().
 */
function whq_register_trumps_cpt() {
  $whq_trump_labels = array(
    'name' => __('Top Trumps', 'whq_trumps'),
    'singular_name' => __('Top Trump', 'whq_trumps'),
    'description' => __('Top Trumps card game.', 'whq_trumps'),
    'add_new' => __('Add New', 'whq_trumps'),
    'add_new_item' => __('Add New Card', 'whq_trumps'),
    'edit_item' => __('Edit Card', 'whq_trumps'),
    'new_item' => __('New Card Created', 'whq_trumps'),
    'view_item' => __('View Card', 'whq_trumps'),
    'all_items' => __('All Cards', 'whq_trumps'),
    'search_items' => __('Search Cards', 'whq_trumps'),
    'not_found' => __('No cards found, create one!', 'whq_trumps'),
    'not_found_in_trash' => __('No cards found in trash', 'whq_trumps'),
  );
  $whq_trump_args = array (
    'labels' => $whq_trump_labels,
    'description' => __('Top Trump cards to be viewed on the Front-End', 'whq_trumps'),
    'public' => true,
    'show_ui' => true,
    'publicly_queryable' => true,
    'exclude_from_search' => true,
    'hierarchical' => false,
    'query_var' => true,
    'supports' => [
      'title',
      'editor',
      'excerpt',
      'thumbnail',
      'custom-fields'
    ],
    'menu_icon' => 'dashicons-admin-page',
    'taxonomies' => ['decks'],
  );
  // Register out top trumps post type with the ID whq_trumps.
  register_post_type('whq_trumps', $whq_trump_args);
}
add_action('init', 'whq_register_trumps_cpt');

// Make sure our plugin isn't called directory and abort.
if (!defined('WPINC')) {
  die;
}
