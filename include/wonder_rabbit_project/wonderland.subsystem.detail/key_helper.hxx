#pragma once

#include "key.hxx"

namespace wonder_rabbit_project
{
  namespace wonderland
  {
    namespace subsystem
    {
      template<class T = void>
      auto key_code_from_glfw3(int key)
        -> key_code_t
      {
        key_code_t fixed_key = key::reserved;
        
        // 1 - 9
        if ( key >= 49 and key <= 57 )
          fixed_key = key::keyboard_1_and_exclamation + key - 49;
        // A - Z
        else if ( key >= 65 and key <= 90 )
          fixed_key = key::keyboard_a_and_A + key - 65;
        // F1 - F12
        else if ( key >= 290 and key <= 301 )
          fixed_key = key::keyboard_f1 + key - 289;
        // F13 - F24
        else if ( key >= 302 and key <= 313 )
          fixed_key = key::keyboard_f13 + key - 302;
        // Num1 - Num9
        else if ( key >= 321 and key <= 329 )
          fixed_key = key::keypad_1_and_end + key - 321;
        // Num{ / * - + ENTER }
        else if ( key >= 331 and key <= 335 )
          fixed_key = key::keypad_slash + key - 331;
        // modifiers ( L{S,C,A,S} R{S,C,A,S} )
        else if ( key >= 340 and key <= 347 )
          fixed_key = key::keyboard_left_shift + key - 340;
        else
          switch (key)
          { case 32: fixed_key = key::keyboard_spacebar; break;
            case 39: fixed_key = key::keyboard_single_quotation_and_double_quotation; break;
            case 44: fixed_key = key::keyboard_comma_and_angle_bracket_open; break;
            case 45: fixed_key = key::keyboard_minus_and_underscore; break;
            case 46: fixed_key = key::keyboard_dot_and_angle_bracket_close; break;
            case 47: fixed_key = key::keyboard_slash_and_question; break;
            case 48: fixed_key = key::keyboard_0_and_round_bracket_end; break;
            case 91: fixed_key = key::keyboard_box_bracket_open_and_curly_bracket_open; break;
            case 92: fixed_key = key::keyboard_back_slash_and_vertical_bar; break;
            case 93: fixed_key = key::keyboard_box_bracket_close_and_curly_bracket_close; break;
            case 96: fixed_key = key::keyboard_grave_accent_and_tilde; break;
            case 161: fixed_key = key::keyboard_non_us_number_mark_and_tilde; break;
            case 162: fixed_key = key::keyboard_non_us_backslash_and_vertical_bar; break;
            case 256: fixed_key = key::keyboard_escape; break;
            case 257: fixed_key = key::keyboard_return_enter; break;
            case 258: fixed_key = key::keyboard_tab; break;
            case 259: fixed_key = key::keyboard_delete_backspace; break;
            case 260: fixed_key = key::keyboard_insert; break;
            case 261: fixed_key = key::keyboard_delete_forward; break;
            case 262: fixed_key = key::keyboard_right_arrow; break;
            case 263: fixed_key = key::keyboard_left_arrow; break;
            case 264: fixed_key = key::keyboard_down_arrow; break;
            case 265: fixed_key = key::keyboard_up_arrow; break;
            case 266: fixed_key = key::keyboard_page_up; break;
            case 267: fixed_key = key::keyboard_page_down; break;
            case 268: fixed_key = key::keyboard_home; break;
            case 269: fixed_key = key::keyboard_end; break;
            case 280: fixed_key = key::keyboard_caps_lock; break;
            case 281: fixed_key = key::keyboard_scroll_lock; break;
            case 282: fixed_key = key::keypad_num_lock_and_clear; break;
            case 283: fixed_key = key::keyboard_print_screen; break;
            case 284: fixed_key = key::keyboard_pause; break;
            case 320: fixed_key = key::keypad_0_and_insert; break;
            case 336: fixed_key = key::keypad_equal; break;
            case 348: fixed_key = key::keyboard_menu; break;
          };
      
        return fixed_key;
      }
      
      template<class T = void>
      auto key_code_from_glfw2(int key)
        -> key_code_t
      {
        key_code_t fixed_key = key::reserved;
        
        // 1 - 9
        if ( key >= 49 and key <= 57 )
          fixed_key = key::keyboard_1_and_exclamation + key - 49;
        // A - Z
        else if ( key >= 65 and key <= 90 )
          fixed_key = key::keyboard_a_and_A + key - 65;
        // F1 - F12
        else if ( key >= 256 + 2 and key <= 256 + 13 )
          fixed_key = key::keyboard_f1 + key - 256 + 2;
        // F13 - F24
        else if ( key >= 256 + 14 and key <= 256 + 25 )
          fixed_key = key::keyboard_f13 + key - 256 + 14;
        // Num1 - Num9
        else if ( key >= 256 + 47 and key <= 256 + 55 )
          fixed_key = key::keypad_1_and_end + key - 256 + 47;
        // Num{ / * - + }
        else if ( key >= 256 + 56 and key <= 256 + 59 )
          fixed_key = key::keypad_slash + key - 256 + 56;
        else
          switch (key)
          { case 32: fixed_key = key::keyboard_spacebar; break;
            case 39: fixed_key = key::keyboard_single_quotation_and_double_quotation; break;
            case 44: fixed_key = key::keyboard_comma_and_angle_bracket_open; break;
            case 45: fixed_key = key::keyboard_minus_and_underscore; break;
            case 46: fixed_key = key::keyboard_dot_and_angle_bracket_close; break;
            case 47: fixed_key = key::keyboard_slash_and_question; break;
            case 48: fixed_key = key::keyboard_0_and_round_bracket_end; break;
            case 91: fixed_key = key::keyboard_box_bracket_open_and_curly_bracket_open; break;
            case 92: fixed_key = key::keyboard_back_slash_and_vertical_bar; break;
            case 93: fixed_key = key::keyboard_box_bracket_close_and_curly_bracket_close; break;
            case 96: fixed_key = key::keyboard_grave_accent_and_tilde; break;
            case 161: fixed_key = key::keyboard_non_us_number_mark_and_tilde; break;
            case 162: fixed_key = key::keyboard_non_us_backslash_and_vertical_bar; break;
            case 256 + 1: fixed_key = key::keyboard_escape; break;
            case 256 + 27: fixed_key = key::keyboard_up_arrow; break;
            case 256 + 28: fixed_key = key::keyboard_down_arrow; break;
            case 256 + 29: fixed_key = key::keyboard_left_arrow; break;
            case 256 + 30: fixed_key = key::keyboard_right_arrow; break;
            case 256 + 31: fixed_key = key::keyboard_left_shift; break;
            case 256 + 32: fixed_key = key::keyboard_right_shift; break;
            case 256 + 33: fixed_key = key::keyboard_left_control; break;
            case 256 + 34: fixed_key = key::keyboard_right_control; break;
            case 256 + 35: fixed_key = key::keyboard_left_alt; break;
            case 256 + 36: fixed_key = key::keyboard_right_alt; break;
            case 256 + 37: fixed_key = key::keyboard_tab; break;
            case 256 + 38: fixed_key = key::keyboard_return_enter; break;
            case 256 + 39: fixed_key = key::keyboard_delete_backspace; break;
            case 256 + 40: fixed_key = key::keyboard_insert; break;
            case 256 + 41: fixed_key = key::keyboard_delete_forward; break;
            case 256 + 42: fixed_key = key::keyboard_page_up; break;
            case 256 + 43: fixed_key = key::keyboard_page_down; break;
            case 256 + 44: fixed_key = key::keyboard_home; break;
            case 256 + 45: fixed_key = key::keyboard_end; break;
            case 256 + 46: fixed_key = key::keypad_0_and_insert; break;
            case 256 + 61: fixed_key = key::keypad_equal; break;
            case 256 + 62: fixed_key = key::keypad_enter; break;
            case 256 + 63: fixed_key = key::keypad_num_lock_and_clear; break;
            case 256 + 64: fixed_key = key::keyboard_caps_lock; break;
            case 256 + 65: fixed_key = key::keyboard_scroll_lock; break;
            case 256 + 66: fixed_key = key::keyboard_pause; break;
            case 256 + 67: fixed_key = key::keyboard_left_gui; break;
            case 256 + 68: fixed_key = key::keyboard_right_gui; break;
            case 256 + 69: fixed_key = key::keyboard_menu; break;
          };
      
        return fixed_key;
      }
      
      template<class T = void>
      auto key_code_from_sdl1(int key)
        -> key_code_t
      {
        key_code_t fixed_key = key::reserved;
        // 1 - 9
        if ( key >= 49 and key <= 57 )
          fixed_key = key::keyboard_1_and_exclamation + key - 49;
        // A - Z
        else if ( key >= 97 and key <= 122 )
          fixed_key = key::keyboard_a_and_A + key - 97;
        // F1 - F12
        else if ( key >= 282 and key <= 293 )
          fixed_key = key::keyboard_f1 + key - 282;
        // F13 - F24
        else if ( key >= 294 and key <= 296 )
          fixed_key = key::keyboard_f13 + key - 294;
        // Num1 - Num9
        else if ( key >= 257 and key <= 265 )
          fixed_key = key::keypad_1_and_end + key - 257;
        // Num{ / * - + }
        else if ( key >= 267 and key <= 270 )
          fixed_key = key::keypad_slash + key - 267;
        else
          switch (key)
          { case 32: fixed_key = key::keyboard_spacebar; break;
            case 39: fixed_key = key::keyboard_single_quotation_and_double_quotation; break;
            case 44: fixed_key = key::keyboard_comma_and_angle_bracket_open; break;
            case 45: fixed_key = key::keyboard_minus_and_underscore; break;
            case 46: fixed_key = key::keyboard_dot_and_angle_bracket_close; break;
            case 47: fixed_key = key::keyboard_slash_and_question; break;
            case 48: fixed_key = key::keyboard_0_and_round_bracket_end; break;
            case 64: fixed_key = key::keyboard_box_bracket_open_and_curly_bracket_open; break;
            case 92: fixed_key = key::keyboard_non_us_backslash_and_vertical_bar; break;
            case 91: fixed_key = key::keyboard_box_bracket_close_and_curly_bracket_close; break;
            case 27: fixed_key = key::keyboard_escape; break;
            case 273: fixed_key = key::keyboard_up_arrow; break;
            case 274: fixed_key = key::keyboard_down_arrow; break;
            case 276: fixed_key = key::keyboard_left_arrow; break;
            case 275: fixed_key = key::keyboard_right_arrow; break;
            case 304: fixed_key = key::keyboard_left_shift; break;
            case 303: fixed_key = key::keyboard_right_shift; break;
            case 306: fixed_key = key::keyboard_left_control; break;
            case 305: fixed_key = key::keyboard_right_control; break;
            case 308: fixed_key = key::keyboard_left_alt; break;
            case 307: fixed_key = key::keyboard_right_alt; break;
            case 9: fixed_key = key::keyboard_tab; break;
            case 13: fixed_key = key::keyboard_return_enter; break;
            case 8: fixed_key = key::keyboard_delete_backspace; break;
            case 277: fixed_key = key::keyboard_insert; break;
            case 127: fixed_key = key::keyboard_delete_forward; break;
            case 280: fixed_key = key::keyboard_page_up; break;
            case 281: fixed_key = key::keyboard_page_down; break;
            case 278: fixed_key = key::keyboard_home; break;
            case 279: fixed_key = key::keyboard_end; break;
            case 256: fixed_key = key::keypad_0_and_insert; break;
            case 272: fixed_key = key::keypad_equal; break;
            case 271: fixed_key = key::keypad_enter; break;
            // SDL-1.2 implements emulation key repeating at NumLock key, its pesky! 
            case 300: break; // fixed_key = key::keypad_num_lock_and_clear; break;
            case 301: fixed_key = key::keyboard_caps_lock; break;
            case 302: fixed_key = key::keyboard_scroll_lock; break;
            case 19: fixed_key = key::keyboard_pause; break;
            case 311: fixed_key = key::keyboard_left_gui; break;
            case 312: fixed_key = key::keyboard_right_gui; break;
            case 319: fixed_key = key::keyboard_menu; break;
            case 266: fixed_key = key::keypad_dot_and_delete; break;
            case 94: fixed_key = key::keyboard_equal_and_plus; break;
            case 59: fixed_key = key::keyboard_semicolon_and_colon; break;
            case 58: fixed_key = key::keyboard_single_quotation_and_double_quotation; break;
            case 93: fixed_key = key::keyboard_back_slash_and_vertical_bar; break;
          };
      
        return fixed_key;
      }
    }
  }
}