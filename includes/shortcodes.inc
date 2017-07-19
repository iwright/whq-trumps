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
function whq_trumps_card_body($deck, $order = 'DESC', $orderby = 'ID') {
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
      $whq_output .= '<li class="whqtrump--card whqtrump--list">';
      $whq_output .= get_the_title();

      // Loop through all custom fields - we do this because a user can create
      // multiple cards and category all of which could include different values.
      $custom_fields = get_post_meta($post->ID, '', true);
      if (!empty($custom_fields)) {
        $whq_output .= '<dl>';
        foreach ($custom_fields as $key => $value) {
          // Ignore WP custom fields e.g. _edit_*
          if (substr($key, 0, 1) !== '_') {
            $whq_output .= '<dt>' . $key . '</dt>';
            $whq_output .= '<dd>' . $value[0] . '</dd>';
          }
        }
        $whq_output .= '</dl>';
      }
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
