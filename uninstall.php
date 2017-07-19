<?php
/**
 * Fired when the plugin is uninstalled.
 */

// If uninstall not called from WordPress, then exit.
if (!defined('WP_UNINSTALL_PLUGIN')) {
  exit;
}

// Delete all posts created.
global $wpdb;
$wpdb->delete($wpdb->posts, ['post_type' => 'whq_trumps']);

// Delete custom terms.
$terms = get_terms('decks');
foreach ($terms as $term) {
  wp_delete_term($term->ID, 'decks');
}

// Deactivate our custom post type.
// Available since core 4.5.
unregister_post_type('whq_trumps');
