<?php
/*
 * Shortcode which lists cards by a specific term.
 */
function whq_trumps_deck($atts){
  $whq_atts = shortcode_atts([
    'deck' => '',
  ], $atts );

  // Set as a function so we can update with AJAX.
  $whq_output = '<div class="whqtrump-wrapper" data-deck="' . $whq_atts['deck'] . '">';
  $whq_output .= '<div class="whqtrump-sort-wrapper">
						<span class="whq-deck-sort card-control">Sort by:</span>
						<select class="whq-deck-sort card-control">
							<option value="ID">Default</option>
							<option value="title">Name</option>
							<option value="rand">Random</option>
						</select>
						<div class="view-cnt">
						  <span class="whq-deck-sort card-control">View by:</span>
              <button id="whqtrump-list" class="list">List</button>
              <button id="whqtrump-grid" class="grid list-active">Grid</button>
            </div>
						</div>';
  $whq_output .= whq_trumps_card_body($whq_atts['deck']);
  $whq_output .= '</div>';
  return $whq_output;
}

/**
 * Custom function to return our cards based on different sorting attributes.
 *
 * @param $deck
 * @param string $order
 * @param string $orderby
 * @return string. Top trumps card output.
 */
function whq_trumps_card_body($deck, $order = 'ASC', $orderby = 'ID') {
  // Set our defaults.
  $whq_post_args = [
    'post_type' => 'whq_trumps',
    'numberposts' => -1,
    'category' => $deck,
    'order' => $order,
    'orderby' => $orderby
  ];

  // Grab all our posts based on the shortcode.
  // We are using WP_Query to give us more control instead of get_posts().
  $whq_deck_query = new WP_Query($whq_post_args);

  // Global $post so we can get meta values (WP 3.5+).
  global $post;

  // Card output.
  $whq_output = '<ul class="whqtrump" data-deck-orderby="' . $orderby . '">';

  // Loop through the cards.
  if ($whq_deck_query->have_posts()) {
    while ($whq_deck_query->have_posts()) {
      $whq_deck_query->the_post();

      // Get our trump card title.
      // I believe this can be improved to use load_template();
      $whq_output .= '<li class="whqtrump--card">';
      $whq_output .= '<header class="whqtrump--intro">';
      if (has_post_thumbnail()) {
        // Thumbnail with custom image size.
        $whq_output .= get_the_post_thumbnail($post->ID, 'whq_trumps_card');
      }
      $whq_output .= '<h3 class="whqtrump--title">' . get_the_title() . '</h3>';
      $whq_output .= '<p>' . get_the_excerpt() . '</p>';
      $whq_output .= '</header>';

      // Get all custom fields for our posts.
      $custom_fields = get_post_meta($post->ID, '', true);

      $whq_output .= '<div class="whqtrump--card-content">';

      // Loop through all custom fields - we do this because a user can create
      // multiple cards and category all of which could include different values.
      if (!empty($custom_fields)) {
        $whq_output .= '<div class="whqtrump--card-togglecontent">';
        $whq_output .= '<dl>';
        foreach ($custom_fields as $key => $value) {
          $data_name = str_replace(' ', '-', strtolower($key));
          $data_level = str_replace(' ', '-', strtolower($value[0]));
          $data_level_numeric = preg_replace('/[^0-9]/','', $data_level);
          // Ignore WP custom fields e.g. _edit_*
          if (substr($key, 0, 1) !== '_') {
            $whq_output .= '<dt data-name="' . $data_name . '">' . $key . ' (' . $value[0] . ')</dt>';
            $whq_output .= '<dd data-stat="stat">';
            $whq_output .= '<div class="whqtrump-stat whqtrump-stat-' . $data_name . '" data-level="' . $data_level_numeric . '"></div>';
            $whq_output .= '</dd>';
          }
        }
        $whq_output .= '</dl>';
        $whq_output .= '</div>';
      }

      // Card content wrapper.
      $whq_output .= '</div>';

      $whq_output .= '</li>';
    }

    // Restore original post data on the page/post.
    wp_reset_postdata();
  } else {
    $whq_output .= '<li>Sorry, no cards available for the selected deck.</li>';
  }

  // Card output.
  $whq_output .= '</ul>';

  // Return cards.
  return $whq_output;
}

/**
 * add_shortcode().
 *
 * Create the shortcode that prints the deck: [whq-trump-deck deck="XXX"].
 */
function whq_trumps_shortcode_init() {
  add_shortcode('whq-trump-deck', 'whq_trumps_deck');
}
add_action( 'init', 'whq_trumps_shortcode_init' );
