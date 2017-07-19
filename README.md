# WHQ Top Trumps

## About
A WordPress plugin which creates a CPT and taxonomy to display Top Trumps cards based on different decks.

### Installation
1. Upload the whq-trumps folder to your `/wp-content/plugins/` directory.
2. Activate the plugin through the 'Plugins' menu in WordPress.
3. Create a few deck terms.
4. Create your Top Trumps card using the WP custom fields for each attribute and assign a deck.
5. Place `[whq-trump-deck deck="XXX]` on the page or post you would like the Top Trumps cards to appear.

Replace XXX with the machine name of your deck.

### List of improvements and features
* On plugin install create "Welcome" cards.
* Improve the cards template to use a theme file which can be overridden in a theme.
* Add more sorting options:
  * Filter by deck.
  * Filter ascending / descending.
  * Filter by custom field.

#### What I don't do...
This plugin creates pure functionality with no styling. Please use the classes provided to theme your way via the active theme.
