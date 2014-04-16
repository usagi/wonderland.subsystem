#pragma once

#include <cstdint>

namespace wonder_rabbit_project
{
  namespace wonderland
  {
    namespace subsystem
    {
      
      using key_code_t = std::uint8_t;
      
      // USB HID Usage page-7 { name, id }
      //enum class key_e
      //  : key_code_t
      struct key_t
      {
        enum
        { reserved
        , keyboard_error_roll_over
        , keyboard_post_fail
        , keyboard_error_undefined
        , keyboard_a_and_A
        , keyboard_b_and_B
        , keyboard_c_and_C
        , keyboard_d_and_D
        , keyboard_e_and_E
        , keyboard_f_and_F
        , keyboard_g_and_G
        , keyboard_h_and_H
        , keyboard_i_and_I
        , keyboard_j_and_J
        , keyboard_k_and_K
        , keyboard_l_and_L
        , keyboard_m_and_M
        , keyboard_n_and_N
        , keyboard_o_and_O
        , keyboard_p_and_P
        , keyboard_q_and_Q
        , keyboard_r_and_R
        , keyboard_s_and_S
        , keyboard_t_and_T
        , keyboard_u_and_U
        , keyboard_v_and_V
        , keyboard_w_and_W
        , keyboard_x_and_X
        , keyboard_y_and_Y
        , keyboard_z_and_Z
        , keyboard_1_and_exclamation // !
        , keyboard_2_and_atmark // @
        , keyboard_3_and_number // #
        , keyboard_4_and_doller // $
        , keyboard_5_and_percent // %
        , keyboard_6_and_caret // ^
        , keyboard_7_and_ampersand // &
        , keyboard_8_and_asterisk // *
        , keyboard_9_and_round_bracket_begin // (
        , keyboard_0_and_round_bracket_end // )
        , keyboard_return_enter
        , keyboard_escape
        , keyboard_delete_backspace
        , keyboard_tab
        , keyboard_spacebar
        , keyboard_minus_and_underscore // - _
        , keyboard_equal_and_plus // = +
        , keyboard_box_bracket_open_and_curly_bracket_open // [ {
        , keyboard_box_bracket_close_and_curly_bracket_close // ] }
        , keyboard_back_slash_and_vertical_bar // |
        , keyboard_non_us_number_mark_and_tilde // ~
        , keyboard_semicolon_and_colon // ; :
        , keyboard_single_quotation_and_double_quotation // ' "
        , keyboard_grave_accent_and_tilde
        , keyboard_comma_and_angle_bracket_open // , <
        , keyboard_dot_and_angle_bracket_close // . >
        , keyboard_slash_and_question // / ?
        , keyboard_caps_lock
        , keyboard_f1
        , keyboard_f2
        , keyboard_f3
        , keyboard_f4
        , keyboard_f5
        , keyboard_f6
        , keyboard_f7
        , keyboard_f8
        , keyboard_f9
        , keyboard_f10
        , keyboard_f11
        , keyboard_f12
        , keyboard_print_screen
        , keyboard_scroll_lock
        , keyboard_pause
        , keyboard_insert
        , keyboard_home
        , keyboard_page_up
        , keyboard_delete_forward
        , keyboard_end
        , keyboard_page_down
        , keyboard_right_arrow
        , keyboard_left_arrow
        , keyboard_down_arrow
        , keyboard_up_arrow
        , keypad_num_lock_and_clear
        , keypad_slash
        , keypad_asterisk
        , keypad_minus
        , keypad_plus
        , keypad_enter
        , keypad_1_and_end
        , keypad_2_and_down_arrow
        , keypad_3_and_page_dn
        , keypad_4_and_left_arrow
        , keypad_5
        , keypad_6_and_right_arrow
        , keypad_7_and_home
        , keypad_8_and_up_arrow
        , keypad_9_and_page_up
        , keypad_0_and_insert
        , keypad_dot_and_delete
        , keyboard_non_us_backslash_and_vertical_bar
        , keyboard_application
        , keyboard_power
        , keypad_equal
        , keyboard_f13
        , keyboard_f14
        , keyboard_f15
        , keyboard_f16
        , keyboard_f17
        , keyboard_f18
        , keyboard_f19
        , keyboard_f20
        , keyboard_f21
        , keyboard_f22
        , keyboard_f23
        , keyboard_f24
        , keyboard_execute
        , keyboard_help
        , keyboard_menu
        , keyboard_select
        , keyboard_stop
        , keyboard_again
        , keyboard_undo
        , keyboard_cut
        , keyboard_copy
        , keyboard_paste
        , keyboard_find
        , keyboard_mute
        , keyboard_volume_up
        , keyboard_vokume_down
        , keyboard_locking_caps_lock
        , keyboard_locking_num_lock
        , keyboard_locking_scroll_lock
        , keypad_comma
        , keypad_equal_sign
        , keyboard_internatinal1
        , keyboard_internatinal2
        , keyboard_internatinal3
        , keyboard_internatinal4
        , keyboard_internatinal5
        , keyboard_internatinal6
        , keyboard_internatinal7
        , keyboard_internatinal8
        , keyboard_internatinal9
        , keyboard_lang1
        , keyboard_lang2
        , keyboard_lang3
        , keyboard_lang4
        , keyboard_lang5
        , keyboard_lang6
        , keyboard_lang7
        , keyboard_lang8
        , keyboard_lang9
        , keyboard_alternate_erase
        , keyboard_sysreq_attention
        , keyboard_cancel
        , keyboard_clear
        , keyboard_prior
        , keyboard_return
        , keyboard_separator
        , keyboard_out
        , keyboard_oper
        , keyboard_clear_again
        , keyboard_cr_sel_props
        , keyboard_ex_sel
        , keyboard_left_control
        , keyboard_left_shift
        , keyboard_left_alt
        , keyboard_left_gui
        , keyboard_right_control
        , keyboard_right_shift
        , keyboard_right_alt
        , keyboard_right_gui
        };
      };
      
      template<key_code_t T_keycode = 0x00> struct key_name_t { };
      template<> struct key_name_t<0x00> { static constexpr const char* value = "reserved"; };
      template<> struct key_name_t<0x01> { static constexpr const char* value = "keyboard_error_roll_over"; };
      template<> struct key_name_t<0x02> { static constexpr const char* value = "keyboard_post_fail"; };
      template<> struct key_name_t<0x03> { static constexpr const char* value = "keyboard_error_undefined"; };
      template<> struct key_name_t<0x04> { static constexpr const char* value = "keyboard_a_and_A"; };
      template<> struct key_name_t<0x05> { static constexpr const char* value = "keyboard_b_and_B"; };
      template<> struct key_name_t<0x06> { static constexpr const char* value = "keyboard_c_and_C"; };
      template<> struct key_name_t<0x07> { static constexpr const char* value = "keyboard_d_and_D"; };
      template<> struct key_name_t<0x08> { static constexpr const char* value = "keyboard_e_and_E"; };
      template<> struct key_name_t<0x09> { static constexpr const char* value = "keyboard_f_and_F"; };
      template<> struct key_name_t<0x0A> { static constexpr const char* value = "keyboard_g_and_G"; };
      template<> struct key_name_t<0x0B> { static constexpr const char* value = "keyboard_h_and_H"; };
      template<> struct key_name_t<0x0C> { static constexpr const char* value = "keyboard_i_and_I"; };
      template<> struct key_name_t<0x0D> { static constexpr const char* value = "keyboard_j_and_J"; };
      template<> struct key_name_t<0x0E> { static constexpr const char* value = "keyboard_k_and_K"; };
      template<> struct key_name_t<0x0F> { static constexpr const char* value = "keyboard_l_and_L"; };
      template<> struct key_name_t<0x10> { static constexpr const char* value = "keyboard_m_and_M"; };
      template<> struct key_name_t<0x11> { static constexpr const char* value = "keyboard_n_and_N"; };
      template<> struct key_name_t<0x12> { static constexpr const char* value = "keyboard_o_and_O"; };
      template<> struct key_name_t<0x13> { static constexpr const char* value = "keyboard_p_and_P"; };
      template<> struct key_name_t<0x14> { static constexpr const char* value = "keyboard_q_and_Q"; };
      template<> struct key_name_t<0x15> { static constexpr const char* value = "keyboard_r_and_R"; };
      template<> struct key_name_t<0x16> { static constexpr const char* value = "keyboard_s_and_S"; };
      template<> struct key_name_t<0x17> { static constexpr const char* value = "keyboard_t_and_T"; };
      template<> struct key_name_t<0x18> { static constexpr const char* value = "keyboard_u_and_U"; };
      template<> struct key_name_t<0x19> { static constexpr const char* value = "keyboard_v_and_V"; };
      template<> struct key_name_t<0x1A> { static constexpr const char* value = "keyboard_w_and_W"; };
      template<> struct key_name_t<0x1B> { static constexpr const char* value = "keyboard_x_and_X"; };
      template<> struct key_name_t<0x1C> { static constexpr const char* value = "keyboard_y_and_Y"; };
      template<> struct key_name_t<0x1D> { static constexpr const char* value = "keyboard_z_and_Z"; };
      template<> struct key_name_t<0x1E> { static constexpr const char* value = "keyboard_1_and_exclamation"; };
      template<> struct key_name_t<0x1F> { static constexpr const char* value = "keyboard_2_and_atmark"; };
      template<> struct key_name_t<0x20> { static constexpr const char* value = "keyboard_3_and_number"; };
      template<> struct key_name_t<0x21> { static constexpr const char* value = "keyboard_4_and_doller"; };
      template<> struct key_name_t<0x22> { static constexpr const char* value = "keyboard_5_and_percent"; };
      template<> struct key_name_t<0x23> { static constexpr const char* value = "keyboard_6_and_caret"; };
      template<> struct key_name_t<0x24> { static constexpr const char* value = "keyboard_7_and_ampersand"; };
      template<> struct key_name_t<0x25> { static constexpr const char* value = "keyboard_8_and_asterisk"; };
      template<> struct key_name_t<0x26> { static constexpr const char* value = "keyboard_9_and_round_bracket_begin"; };
      template<> struct key_name_t<0x27> { static constexpr const char* value = "keyboard_0_and_round_bracket_end"; };
      template<> struct key_name_t<0x28> { static constexpr const char* value = "keyboard_return_enter"; };
      template<> struct key_name_t<0x29> { static constexpr const char* value = "keyboard_escape"; };
      template<> struct key_name_t<0x2A> { static constexpr const char* value = "keyboard_delete_backspace"; };
      template<> struct key_name_t<0x2B> { static constexpr const char* value = "keyboard_tab"; };
      template<> struct key_name_t<0x2C> { static constexpr const char* value = "keyboard_spacebar"; };
      template<> struct key_name_t<0x2D> { static constexpr const char* value = "keyboard_minus_and_underscore"; };
      template<> struct key_name_t<0x2E> { static constexpr const char* value = "keyboard_equal_and_plus"; };
      template<> struct key_name_t<0x2F> { static constexpr const char* value = "keyboard_box_bracket_open_and_curly_bracket_open"; };
      template<> struct key_name_t<0x30> { static constexpr const char* value = "keyboard_box_bracket_close_and_curly_bracket_close"; };
      template<> struct key_name_t<0x31> { static constexpr const char* value = "keyboard_back_slash_and_vertical_bar"; };
      template<> struct key_name_t<0x32> { static constexpr const char* value = "keyboard_non_us_number_mark_and_tilde"; };
      template<> struct key_name_t<0x33> { static constexpr const char* value = "keyboard_semicolon_and_colon"; };
      template<> struct key_name_t<0x34> { static constexpr const char* value = "keyboard_single_quotation_and_double_quotation"; };
      template<> struct key_name_t<0x35> { static constexpr const char* value = "keyboard_grave_accent_and_tilde"; };
      template<> struct key_name_t<0x36> { static constexpr const char* value = "keyboard_comma_and_angle_bracket_open"; };
      template<> struct key_name_t<0x37> { static constexpr const char* value = "keyboard_dot_and_angle_bracket_close"; };
      template<> struct key_name_t<0x38> { static constexpr const char* value = "keyboard_slash_and_question"; };
      template<> struct key_name_t<0x39> { static constexpr const char* value = "keyboard_caps_lock"; };
      template<> struct key_name_t<0x3A> { static constexpr const char* value = "keyboard_f1"; };
      template<> struct key_name_t<0x3B> { static constexpr const char* value = "keyboard_f2"; };
      template<> struct key_name_t<0x3C> { static constexpr const char* value = "keyboard_f3"; };
      template<> struct key_name_t<0x3D> { static constexpr const char* value = "keyboard_f4"; };
      template<> struct key_name_t<0x3E> { static constexpr const char* value = "keyboard_f5"; };
      template<> struct key_name_t<0x3F> { static constexpr const char* value = "keyboard_f6"; };
      template<> struct key_name_t<0x40> { static constexpr const char* value = "keyboard_f7"; };
      template<> struct key_name_t<0x41> { static constexpr const char* value = "keyboard_f8"; };
      template<> struct key_name_t<0x42> { static constexpr const char* value = "keyboard_f9"; };
      template<> struct key_name_t<0x43> { static constexpr const char* value = "keyboard_f10"; };
      template<> struct key_name_t<0x44> { static constexpr const char* value = "keyboard_f11"; };
      template<> struct key_name_t<0x45> { static constexpr const char* value = "keyboard_f12"; };
      template<> struct key_name_t<0x46> { static constexpr const char* value = "keyboard_print_screen"; };
      template<> struct key_name_t<0x47> { static constexpr const char* value = "keyboard_scroll_lock"; };
      template<> struct key_name_t<0x48> { static constexpr const char* value = "keyboard_pause"; };
      template<> struct key_name_t<0x49> { static constexpr const char* value = "keyboard_insert"; };
      template<> struct key_name_t<0x4A> { static constexpr const char* value = "keyboard_home"; };
      template<> struct key_name_t<0x4B> { static constexpr const char* value = "keyboard_page_up"; };
      template<> struct key_name_t<0x4C> { static constexpr const char* value = "keyboard_delete_forward"; };
      template<> struct key_name_t<0x4D> { static constexpr const char* value = "keyboard_end"; };
      template<> struct key_name_t<0x4E> { static constexpr const char* value = "keyboard_page_down"; };
      template<> struct key_name_t<0x4F> { static constexpr const char* value = "keyboard_right_arrow"; };
      template<> struct key_name_t<0x50> { static constexpr const char* value = "keyboard_left_arrow"; };
      template<> struct key_name_t<0x51> { static constexpr const char* value = "keyboard_down_arrow"; };
      template<> struct key_name_t<0x52> { static constexpr const char* value = "keyboard_up_arrow"; };
      template<> struct key_name_t<0x53> { static constexpr const char* value = "keypad_num_lock_and_clear"; };
      template<> struct key_name_t<0x54> { static constexpr const char* value = "keypad_slash"; };
      template<> struct key_name_t<0x55> { static constexpr const char* value = "keypad_asterisk"; };
      template<> struct key_name_t<0x56> { static constexpr const char* value = "keypad_minus"; };
      template<> struct key_name_t<0x57> { static constexpr const char* value = "keypad_plus"; };
      template<> struct key_name_t<0x58> { static constexpr const char* value = "keypad_enter"; };
      template<> struct key_name_t<0x59> { static constexpr const char* value = "keypad_1_and_end"; };
      template<> struct key_name_t<0x5A> { static constexpr const char* value = "keypad_2_and_down_arrow"; };
      template<> struct key_name_t<0x5B> { static constexpr const char* value = "keypad_3_and_page_dn"; };
      template<> struct key_name_t<0x5C> { static constexpr const char* value = "keypad_4_and_left_arrow"; };
      template<> struct key_name_t<0x5D> { static constexpr const char* value = "keypad_5"; };
      template<> struct key_name_t<0x5E> { static constexpr const char* value = "keypad_6_and_right_arrow"; };
      template<> struct key_name_t<0x5F> { static constexpr const char* value = "keypad_7_and_home"; };
      template<> struct key_name_t<0x60> { static constexpr const char* value = "keypad_8_and_up_arrow"; };
      template<> struct key_name_t<0x61> { static constexpr const char* value = "keypad_9_and_page_up"; };
      template<> struct key_name_t<0x62> { static constexpr const char* value = "keypad_0x_and_insert"; };
      template<> struct key_name_t<0x63> { static constexpr const char* value = "keypad_dot_and_delete"; };
      template<> struct key_name_t<0x64> { static constexpr const char* value = "keyboard_non_us_backslash_and_vertical_bar"; };
      template<> struct key_name_t<0x65> { static constexpr const char* value = "keyboard_application"; };
      template<> struct key_name_t<0x66> { static constexpr const char* value = "keyboard_power"; };
      template<> struct key_name_t<0x67> { static constexpr const char* value = "keypad_equal"; };
      template<> struct key_name_t<0x68> { static constexpr const char* value = "keyboard_f13"; };
      template<> struct key_name_t<0x69> { static constexpr const char* value = "keyboard_f14"; };
      template<> struct key_name_t<0x6A> { static constexpr const char* value = "keyboard_f15"; };
      template<> struct key_name_t<0x6B> { static constexpr const char* value = "keyboard_f16"; };
      template<> struct key_name_t<0x6C> { static constexpr const char* value = "keyboard_f17"; };
      template<> struct key_name_t<0x6D> { static constexpr const char* value = "keyboard_f18"; };
      template<> struct key_name_t<0x6E> { static constexpr const char* value = "keyboard_f19"; };
      template<> struct key_name_t<0x6F> { static constexpr const char* value = "keyboard_f20"; };
      template<> struct key_name_t<0x70> { static constexpr const char* value = "keyboard_f21"; };
      template<> struct key_name_t<0x71> { static constexpr const char* value = "keyboard_f22"; };
      template<> struct key_name_t<0x72> { static constexpr const char* value = "keyboard_f23"; };
      template<> struct key_name_t<0x73> { static constexpr const char* value = "keyboard_f24"; };
      template<> struct key_name_t<0x74> { static constexpr const char* value = "keyboard_execute"; };
      template<> struct key_name_t<0x75> { static constexpr const char* value = "keyboard_help"; };
      template<> struct key_name_t<0x76> { static constexpr const char* value = "keyboard_menu"; };
      template<> struct key_name_t<0x77> { static constexpr const char* value = "keyboard_select"; };
      template<> struct key_name_t<0x78> { static constexpr const char* value = "keyboard_stop"; };
      template<> struct key_name_t<0x79> { static constexpr const char* value = "keyboard_again"; };
      template<> struct key_name_t<0x7A> { static constexpr const char* value = "keyboard_undo"; };
      template<> struct key_name_t<0x7B> { static constexpr const char* value = "keyboard_cut"; };
      template<> struct key_name_t<0x7C> { static constexpr const char* value = "keyboard_copy"; };
      template<> struct key_name_t<0x7D> { static constexpr const char* value = "keyboard_paste"; };
      template<> struct key_name_t<0x7E> { static constexpr const char* value = "keyboard_find"; };
      template<> struct key_name_t<0x7F> { static constexpr const char* value = "keyboard_mute"; };
      template<> struct key_name_t<0x80> { static constexpr const char* value = "keyboard_volume_up"; };
      template<> struct key_name_t<0x81> { static constexpr const char* value = "keyboard_vokume_down"; };
      template<> struct key_name_t<0x82> { static constexpr const char* value = "keyboard_locking_caps_lock"; };
      template<> struct key_name_t<0x83> { static constexpr const char* value = "keyboard_locking_num_lock"; };
      template<> struct key_name_t<0x84> { static constexpr const char* value = "keyboard_locking_scroll_lock"; };
      template<> struct key_name_t<0x85> { static constexpr const char* value = "keypad_comma"; };
      template<> struct key_name_t<0x86> { static constexpr const char* value = "keypad_equal_sign"; };
      template<> struct key_name_t<0x87> { static constexpr const char* value = "keyboard_internatinal1"; };
      template<> struct key_name_t<0x88> { static constexpr const char* value = "keyboard_internatinal2"; };
      template<> struct key_name_t<0x89> { static constexpr const char* value = "keyboard_internatinal3"; };
      template<> struct key_name_t<0x8A> { static constexpr const char* value = "keyboard_internatinal4"; };
      template<> struct key_name_t<0x8B> { static constexpr const char* value = "keyboard_internatinal5"; };
      template<> struct key_name_t<0x8C> { static constexpr const char* value = "keyboard_internatinal6"; };
      template<> struct key_name_t<0x8D> { static constexpr const char* value = "keyboard_internatinal7"; };
      template<> struct key_name_t<0x8E> { static constexpr const char* value = "keyboard_internatinal8"; };
      template<> struct key_name_t<0x8F> { static constexpr const char* value = "keyboard_internatinal9"; };
      template<> struct key_name_t<0x90> { static constexpr const char* value = "keyboard_lang1"; };
      template<> struct key_name_t<0x91> { static constexpr const char* value = "keyboard_lang2"; };
      template<> struct key_name_t<0x92> { static constexpr const char* value = "keyboard_lang3"; };
      template<> struct key_name_t<0x93> { static constexpr const char* value = "keyboard_lang4"; };
      template<> struct key_name_t<0x94> { static constexpr const char* value = "keyboard_lang5"; };
      template<> struct key_name_t<0x95> { static constexpr const char* value = "keyboard_lang6"; };
      template<> struct key_name_t<0x96> { static constexpr const char* value = "keyboard_lang7"; };
      template<> struct key_name_t<0x97> { static constexpr const char* value = "keyboard_lang8"; };
      template<> struct key_name_t<0x98> { static constexpr const char* value = "keyboard_lang9"; };
      template<> struct key_name_t<0x99> { static constexpr const char* value = "keyboard_alternate_erase"; };
      template<> struct key_name_t<0x9A> { static constexpr const char* value = "keyboard_sysreq_attention"; };
      template<> struct key_name_t<0x9B> { static constexpr const char* value = "keyboard_cancel"; };
      template<> struct key_name_t<0x9C> { static constexpr const char* value = "keyboard_clear"; };
      template<> struct key_name_t<0x9D> { static constexpr const char* value = "keyboard_prior"; };
      template<> struct key_name_t<0x9E> { static constexpr const char* value = "keyboard_return"; };
      template<> struct key_name_t<0x9F> { static constexpr const char* value = "keyboard_separator"; };
      template<> struct key_name_t<0xA0> { static constexpr const char* value = "keyboard_out"; };
      template<> struct key_name_t<0xA1> { static constexpr const char* value = "keyboard_oper"; };
      template<> struct key_name_t<0xA2> { static constexpr const char* value = "keyboard_clear_again"; };
      template<> struct key_name_t<0xA3> { static constexpr const char* value = "keyboard_cr_sel_props"; };
      template<> struct key_name_t<0xA4> { static constexpr const char* value = "keyboard_ex_sel"; };
      template<> struct key_name_t<0xE0> { static constexpr const char* value = "keyboard_left_control"; };
      template<> struct key_name_t<0xE1> { static constexpr const char* value = "keyboard_left_shift"; };
      template<> struct key_name_t<0xE2> { static constexpr const char* value = "keyboard_left_alt"; };
      template<> struct key_name_t<0xE3> { static constexpr const char* value = "keyboard_left_gui"; };
      template<> struct key_name_t<0xE4> { static constexpr const char* value = "keyboard_right_control"; };
      template<> struct key_name_t<0xE5> { static constexpr const char* value = "keyboard_right_shift"; };
      template<> struct key_name_t<0xE6> { static constexpr const char* value = "keyboard_right_alt"; };
      template<> struct key_name_t<0xE7> { static constexpr const char* value = "keyboard_right_gui"; };
      
      // easy for use
      using key = key_t;
      template<key_code_t T_keycode> using key_name = key_name_t<T_keycode>;
    }
  }
}