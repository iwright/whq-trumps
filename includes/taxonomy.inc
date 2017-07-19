<?php
/**
 * register_taxonomy().
 */
function whq_trumps_taxonomy() {
  // Add Decks to whq_trumps CPT.
  register_taxonomy(
    'decks',
    'whq_trumps',
    [
      'hierarchical' => true,
      'labels' => [
        'name' => __('Decks', 'whq_trumps'),
        'singular_name' => __('Deck', 'whq_trumps'),
        'search_items' =>  __('Search Decks', 'whq_trumps'),
        'all_items' => __('All Decks', 'whq_trumps'),
        'edit_item' => __('Edit Deck', 'whq_trumps'),
        'update_item' => __('Update Deck', 'whq_trumps'),
        'add_new_item' => __('Add New Deck', 'whq_trumps'),
        'new_item_name' => __('New Deck Name', 'whq_trumps'),
        'menu_name' => __('Decks', 'whq_trumps')
      ]
    ]
  );
}
add_action('init', 'whq_trumps_taxonomy', 0);
