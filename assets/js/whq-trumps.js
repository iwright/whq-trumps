(function($) {
  'use strict';
  $(function() {
    // Check to see when our ordering select is changed.
    $('.whq-deck-sort').on('change', function() {
      // Ajax request (Sends data to PHP)
      $.ajax({
        type: 'POST',
        url: whq_trumps_ajax.ajax_url,
        data: {
          // See PHP (includes/ajax.php)
          action: 'whq_trumps_card_request',
          _ajax_nonce: whq_trumps_ajax.nonce,
          // Data to send.
          whq_trumps_deck: $('.whqtrump-wrapper').data('deck'),
          whq_trumps_orderby: $(this).val()
        },
        // Our request has succeeded/
        // Remove the current list and add our new list to the DOM.
        success:function(data) {
          $('.whqtrump').remove();
          $('.whqtrump-wrapper').append(data);
        },
        // Our request has failed - let the user know with an alert.
        error:function(errorThrown) {
          alert(errorThrown);
        }
      });
    });

    // List and grid view.
    $('#whqtrump-grid').on('click', function() {
      $('.whqtrump--card').removeClass('whqtrump--list');
    });
    $('#whqtrump-list').on('click', function() {
      $('.whqtrump--card').addClass('whqtrump--list');
    });
  });
})(jQuery);
