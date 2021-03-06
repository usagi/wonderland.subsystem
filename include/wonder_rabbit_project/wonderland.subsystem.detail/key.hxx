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
        // US keytop definition
        , keyboard_error_roll_over
        , keyboard_post_fail
        , keyboard_error_undefined
        , keyboard_a_and_A, a = keyboard_a_and_A, A = keyboard_a_and_A
        , keyboard_b_and_B, b = keyboard_b_and_B, B = keyboard_b_and_B
        , keyboard_c_and_C, c = keyboard_c_and_C, C = keyboard_c_and_C
        , keyboard_d_and_D, d = keyboard_d_and_D, D = keyboard_d_and_D
        , keyboard_e_and_E, e = keyboard_e_and_E, E = keyboard_e_and_E
        , keyboard_f_and_F, f = keyboard_f_and_F, F = keyboard_f_and_F
        , keyboard_g_and_G, g = keyboard_g_and_G, G = keyboard_g_and_G
        , keyboard_h_and_H, h = keyboard_h_and_H, H = keyboard_h_and_H
        , keyboard_i_and_I, i = keyboard_i_and_I, I = keyboard_i_and_I
        , keyboard_j_and_J, j = keyboard_j_and_J, J = keyboard_j_and_J
        , keyboard_k_and_K, k = keyboard_k_and_K, K = keyboard_k_and_K
        , keyboard_l_and_L, l = keyboard_l_and_L, L = keyboard_l_and_L
        , keyboard_m_and_M, m = keyboard_m_and_M, M = keyboard_m_and_M
        , keyboard_n_and_N, n = keyboard_n_and_N, N = keyboard_n_and_N
        , keyboard_o_and_O, o = keyboard_o_and_O, O = keyboard_o_and_O
        , keyboard_p_and_P, p = keyboard_p_and_P, P = keyboard_p_and_P
        , keyboard_q_and_Q, q = keyboard_q_and_Q, Q = keyboard_q_and_Q
        , keyboard_r_and_R, r = keyboard_r_and_R, R = keyboard_r_and_R
        , keyboard_s_and_S, s = keyboard_s_and_S, S = keyboard_s_and_S
        , keyboard_t_and_T, t = keyboard_t_and_T, T = keyboard_t_and_T
        , keyboard_u_and_U, u = keyboard_u_and_U, U = keyboard_u_and_U
        , keyboard_v_and_V, v = keyboard_v_and_V, V = keyboard_v_and_V
        , keyboard_w_and_W, w = keyboard_w_and_W, W = keyboard_w_and_W
        , keyboard_x_and_X, x = keyboard_x_and_X, X = keyboard_x_and_X
        , keyboard_y_and_Y, y = keyboard_y_and_Y, Y = keyboard_y_and_Y
        , keyboard_z_and_Z, z = keyboard_z_and_Z, Z = keyboard_z_and_Z
        , keyboard_1_and_exclamation, _1 = keyboard_1_and_exclamation, exclamation = keyboard_1_and_exclamation // !
        , keyboard_2_and_atmark     , _2 = keyboard_2_and_atmark, atmark = keyboard_2_and_atmark // @
        , keyboard_3_and_number     , _3 = keyboard_3_and_number, number = keyboard_3_and_number // #
        , keyboard_4_and_doller     , _4 = keyboard_4_and_doller, doller = keyboard_4_and_doller // $
        , keyboard_5_and_percent    , _5 = keyboard_5_and_percent, percent = keyboard_5_and_percent // %
        , keyboard_6_and_caret      , _6 = keyboard_6_and_caret, caret = keyboard_6_and_caret // ^
        , keyboard_7_and_ampersand  , _7 = keyboard_7_and_ampersand, ampersand = keyboard_7_and_ampersand // &
        , keyboard_8_and_asterisk   , _8 = keyboard_8_and_asterisk, asterisk = keyboard_8_and_asterisk // *
        , keyboard_9_and_round_bracket_begin, _9 = keyboard_9_and_round_bracket_begin, round_bracket_begin = keyboard_9_and_round_bracket_begin // (
        , keyboard_0_and_round_bracket_end  , _0 = keyboard_0_and_round_bracket_end, round_bracket_end = keyboard_0_and_round_bracket_end // )
        , keyboard_return_enter     , enter = keyboard_return_enter
        , keyboard_escape           , escape = keyboard_escape
        , keyboard_delete_backspace , backspace = keyboard_delete_backspace
        , keyboard_tab              , tab = keyboard_tab
        , keyboard_spacebar         , space = keyboard_spacebar, spacebar = keyboard_spacebar
        , keyboard_minus_and_underscore, minus = keyboard_minus_and_underscore, underscore = keyboard_minus_and_underscore // - _
        , keyboard_equal_and_plus      , equal = keyboard_equal_and_plus, plus = keyboard_equal_and_plus // = +
        , keyboard_box_bracket_open_and_curly_bracket_open  , box_bracket_open = keyboard_box_bracket_open_and_curly_bracket_open, curly_bracket_open = keyboard_box_bracket_open_and_curly_bracket_open // [ {
        , keyboard_box_bracket_close_and_curly_bracket_close, box_bracket_close = keyboard_box_bracket_close_and_curly_bracket_close, curly_bracket_close = keyboard_box_bracket_close_and_curly_bracket_close // ] }
        , keyboard_back_slash_and_vertical_bar  , back_slash = keyboard_back_slash_and_vertical_bar, vertical_bar = keyboard_back_slash_and_vertical_bar // |
        , keyboard_non_us_number_mark_and_tilde , non_us_number_mark = keyboard_non_us_number_mark_and_tilde // ~
        , keyboard_semicolon_and_colon          , semicolon = keyboard_semicolon_and_colon, colon = keyboard_semicolon_and_colon // ; :
        , keyboard_single_quotation_and_double_quotation, single_quotation = keyboard_single_quotation_and_double_quotation, double_quotation = keyboard_single_quotation_and_double_quotation // ' "
        , keyboard_grave_accent_and_tilde      , grave_accent = keyboard_grave_accent_and_tilde
        , keyboard_comma_and_angle_bracket_open, comma = keyboard_comma_and_angle_bracket_open, angle_bracket_open = keyboard_comma_and_angle_bracket_open // , <
        , keyboard_dot_and_angle_bracket_close , dot = keyboard_dot_and_angle_bracket_close, angle_bracket_close = keyboard_dot_and_angle_bracket_close // . >
        , keyboard_slash_and_question          , slash = keyboard_slash_and_question, question = keyboard_slash_and_question // / ?
        , keyboard_caps_lock                   , caps_lock = keyboard_caps_lock
        , keyboard_f1, f1 = keyboard_f1
        , keyboard_f2, f2 = keyboard_f2
        , keyboard_f3, f3 = keyboard_f3
        , keyboard_f4, f4 = keyboard_f4
        , keyboard_f5, f5 = keyboard_f5
        , keyboard_f6, f6 = keyboard_f6
        , keyboard_f7, f7 = keyboard_f7
        , keyboard_f8, f8 = keyboard_f8
        , keyboard_f9, f9 = keyboard_f9
        , keyboard_f10, f10 = keyboard_f10
        , keyboard_f11, f11 = keyboard_f11
        , keyboard_f12, f12 = keyboard_f12
        , keyboard_print_screen, print_screen = keyboard_print_screen
        , keyboard_scroll_lock , scroll_lock = keyboard_scroll_lock
        , keyboard_pause       , pause = keyboard_pause
        , keyboard_insert      , insert = keyboard_insert
        , keyboard_home        , home = keyboard_home
        , keyboard_page_up     , page_up = keyboard_page_up
        , keyboard_delete_forward, delete_forward = keyboard_delete_forward
        , keyboard_end         , end = keyboard_end
        , keyboard_page_down   , page_down = keyboard_page_down
        , keyboard_right_arrow , right_arrow = keyboard_right_arrow
        , keyboard_left_arrow  , left_arrow = keyboard_left_arrow
        , keyboard_down_arrow  , down_arrow = keyboard_down_arrow
        , keyboard_up_arrow    , up_arrow = keyboard_up_arrow
        , keypad_num_lock_and_clear, num_lock = keypad_num_lock_and_clear
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
        , keyboard_non_us_backslash_and_vertical_bar, non_us_backslash = keyboard_non_us_backslash_and_vertical_bar
        , keyboard_application, application = keyboard_application
        , keyboard_power, power = keyboard_power
        , keypad_equal
        , keyboard_f13, f13 = keyboard_f13
        , keyboard_f14, f14 = keyboard_f14
        , keyboard_f15, f15 = keyboard_f15
        , keyboard_f16, f16 = keyboard_f16
        , keyboard_f17, f17 = keyboard_f17
        , keyboard_f18, f18 = keyboard_f18
        , keyboard_f19, f19 = keyboard_f19
        , keyboard_f20, f20 = keyboard_f20
        , keyboard_f21, f21 = keyboard_f21
        , keyboard_f22, f22 = keyboard_f22
        , keyboard_f23, f23 = keyboard_f23
        , keyboard_f24, f24 = keyboard_f24
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
        , keyboard_international1
        , keyboard_international2
        , keyboard_international3
        , keyboard_international4
        , keyboard_international5
        , keyboard_international6
        , keyboard_international7
        , keyboard_international8
        , keyboard_international9
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
        // 0xA5-0xAF: Reserved
        , keypad_00 = 0xB0
        , keypad_000
        , thousands_separator
        , decimal_separator
        , currency_unit
        , currency_sub_unit
        , keypad_round_bracket_open
        , keypad_round_bracket_close
        , keypad_curly_bracket_open
        , keypad_curly_bracket_close
        , keypad_tab
        , keypad_backspace
        , keypad_a
        , keypad_b
        , keypad_c
        , keypad_d
        , keypad_e
        , keypad_f
        , keypad_xor
        , keypad_hat
        , keypad_parcent
        , keypad_left_angle_bracket
        , keypad_right_angle_bracket
        , keypad_and
        , keypad_and_and
        , keypad_virtical_bar
        , keypad_virtical_bar_virtical_bar
        , keypad_colon
        , keypad_number
        , keypad_space
        , keypad_exclamation
        , keypad_memory_store
        , keypad_memory_recall
        , keypad_memory_clear
        , keypad_memory_add
        , keypad_memory_subtract
        , keypad_memory_multiply
        , keypad_memory_divide
        , keypad_plus_minus
        , keypad_clear
        , keypad_clear_entry
        , keypad_binary
        , keypad_octal
        , keypad_decimal
        , keypad_hexadecimal
        // 0xDE-0xDF : Reserved
        , keyboard_left_control = 0xE0, left_control = keyboard_left_control
        , keyboard_left_shift  , left_shift   = keyboard_left_shift
        , keyboard_left_alt    , left_alt     = keyboard_left_alt
        , keyboard_left_gui    , left_gui     = keyboard_left_gui
        , keyboard_right_control, right_control = keyboard_right_control
        , keyboard_right_shift  , right_shift   = keyboard_right_shift
        , keyboard_right_alt    , right_alt     = keyboard_right_alt
        , keyboard_right_gui    , right_gui     = keyboard_right_gui
        // Japanese key-top support
        , japanese_katakana_hiragana = keyboard_international2
        , japanese_caret             = keyboard_equal_and_plus
        , japanese_yen               = keyboard_international3
        , japanese_atmark            = keyboard_box_bracket_open_and_curly_bracket_open
        , japanese_box_bracket_open  = keyboard_box_bracket_close_and_curly_bracket_close
        , japanese_colon             = keyboard_single_quotation_and_double_quotation
        , japanese_henkan            = keyboard_international4
        , japanese_hankaku_zenkaku   = keyboard_grave_accent_and_tilde
        };
      };
      
      template<key_code_t T_keycode = 0x00> struct key_name_t { };
      template<> struct key_name_t<0x00> { static constexpr auto value() { return "reserved"; } };
      template<> struct key_name_t<0x01> { static constexpr auto value() { return "keyboard_error_roll_over"; } };
      template<> struct key_name_t<0x02> { static constexpr auto value() { return "keyboard_post_fail"; } };
      template<> struct key_name_t<0x03> { static constexpr auto value() { return "keyboard_error_undefined"; } };
      template<> struct key_name_t<0x04> { static constexpr auto value() { return "keyboard_a_and_A"; } };
      template<> struct key_name_t<0x05> { static constexpr auto value() { return "keyboard_b_and_B"; } };
      template<> struct key_name_t<0x06> { static constexpr auto value() { return "keyboard_c_and_C"; } };
      template<> struct key_name_t<0x07> { static constexpr auto value() { return "keyboard_d_and_D"; } };
      template<> struct key_name_t<0x08> { static constexpr auto value() { return "keyboard_e_and_E"; } };
      template<> struct key_name_t<0x09> { static constexpr auto value() { return "keyboard_f_and_F"; } };
      template<> struct key_name_t<0x0A> { static constexpr auto value() { return "keyboard_g_and_G"; } };
      template<> struct key_name_t<0x0B> { static constexpr auto value() { return "keyboard_h_and_H"; } };
      template<> struct key_name_t<0x0C> { static constexpr auto value() { return "keyboard_i_and_I"; } };
      template<> struct key_name_t<0x0D> { static constexpr auto value() { return "keyboard_j_and_J"; } };
      template<> struct key_name_t<0x0E> { static constexpr auto value() { return "keyboard_k_and_K"; } };
      template<> struct key_name_t<0x0F> { static constexpr auto value() { return "keyboard_l_and_L"; } };
      template<> struct key_name_t<0x10> { static constexpr auto value() { return "keyboard_m_and_M"; } };
      template<> struct key_name_t<0x11> { static constexpr auto value() { return "keyboard_n_and_N"; } };
      template<> struct key_name_t<0x12> { static constexpr auto value() { return "keyboard_o_and_O"; } };
      template<> struct key_name_t<0x13> { static constexpr auto value() { return "keyboard_p_and_P"; } };
      template<> struct key_name_t<0x14> { static constexpr auto value() { return "keyboard_q_and_Q"; } };
      template<> struct key_name_t<0x15> { static constexpr auto value() { return "keyboard_r_and_R"; } };
      template<> struct key_name_t<0x16> { static constexpr auto value() { return "keyboard_s_and_S"; } };
      template<> struct key_name_t<0x17> { static constexpr auto value() { return "keyboard_t_and_T"; } };
      template<> struct key_name_t<0x18> { static constexpr auto value() { return "keyboard_u_and_U"; } };
      template<> struct key_name_t<0x19> { static constexpr auto value() { return "keyboard_v_and_V"; } };
      template<> struct key_name_t<0x1A> { static constexpr auto value() { return "keyboard_w_and_W"; } };
      template<> struct key_name_t<0x1B> { static constexpr auto value() { return "keyboard_x_and_X"; } };
      template<> struct key_name_t<0x1C> { static constexpr auto value() { return "keyboard_y_and_Y"; } };
      template<> struct key_name_t<0x1D> { static constexpr auto value() { return "keyboard_z_and_Z"; } };
      template<> struct key_name_t<0x1E> { static constexpr auto value() { return "keyboard_1_and_exclamation"; } };
      template<> struct key_name_t<0x1F> { static constexpr auto value() { return "keyboard_2_and_atmark"; } };
      template<> struct key_name_t<0x20> { static constexpr auto value() { return "keyboard_3_and_number"; } };
      template<> struct key_name_t<0x21> { static constexpr auto value() { return "keyboard_4_and_doller"; } };
      template<> struct key_name_t<0x22> { static constexpr auto value() { return "keyboard_5_and_percent"; } };
      template<> struct key_name_t<0x23> { static constexpr auto value() { return "keyboard_6_and_caret"; } };
      template<> struct key_name_t<0x24> { static constexpr auto value() { return "keyboard_7_and_ampersand"; } };
      template<> struct key_name_t<0x25> { static constexpr auto value() { return "keyboard_8_and_asterisk"; } };
      template<> struct key_name_t<0x26> { static constexpr auto value() { return "keyboard_9_and_round_bracket_begin"; } };
      template<> struct key_name_t<0x27> { static constexpr auto value() { return "keyboard_0_and_round_bracket_end"; } };
      template<> struct key_name_t<0x28> { static constexpr auto value() { return "keyboard_return_enter"; } };
      template<> struct key_name_t<0x29> { static constexpr auto value() { return "keyboard_escape"; } };
      template<> struct key_name_t<0x2A> { static constexpr auto value() { return "keyboard_delete_backspace"; } };
      template<> struct key_name_t<0x2B> { static constexpr auto value() { return "keyboard_tab"; } };
      template<> struct key_name_t<0x2C> { static constexpr auto value() { return "keyboard_spacebar"; } };
      template<> struct key_name_t<0x2D> { static constexpr auto value() { return "keyboard_minus_and_underscore"; } };
      template<> struct key_name_t<0x2E> { static constexpr auto value() { return "keyboard_equal_and_plus"; } };
      template<> struct key_name_t<0x2F> { static constexpr auto value() { return "keyboard_box_bracket_open_and_curly_bracket_open"; } };
      template<> struct key_name_t<0x30> { static constexpr auto value() { return "keyboard_box_bracket_close_and_curly_bracket_close"; } };
      template<> struct key_name_t<0x31> { static constexpr auto value() { return "keyboard_back_slash_and_vertical_bar"; } };
      template<> struct key_name_t<0x32> { static constexpr auto value() { return "keyboard_non_us_number_mark_and_tilde"; } };
      template<> struct key_name_t<0x33> { static constexpr auto value() { return "keyboard_semicolon_and_colon"; } };
      template<> struct key_name_t<0x34> { static constexpr auto value() { return "keyboard_single_quotation_and_double_quotation"; } };
      template<> struct key_name_t<0x35> { static constexpr auto value() { return "keyboard_grave_accent_and_tilde"; } };
      template<> struct key_name_t<0x36> { static constexpr auto value() { return "keyboard_comma_and_angle_bracket_open"; } };
      template<> struct key_name_t<0x37> { static constexpr auto value() { return "keyboard_dot_and_angle_bracket_close"; } };
      template<> struct key_name_t<0x38> { static constexpr auto value() { return "keyboard_slash_and_question"; } };
      template<> struct key_name_t<0x39> { static constexpr auto value() { return "keyboard_caps_lock"; } };
      template<> struct key_name_t<0x3A> { static constexpr auto value() { return "keyboard_f1"; } };
      template<> struct key_name_t<0x3B> { static constexpr auto value() { return "keyboard_f2"; } };
      template<> struct key_name_t<0x3C> { static constexpr auto value() { return "keyboard_f3"; } };
      template<> struct key_name_t<0x3D> { static constexpr auto value() { return "keyboard_f4"; } };
      template<> struct key_name_t<0x3E> { static constexpr auto value() { return "keyboard_f5"; } };
      template<> struct key_name_t<0x3F> { static constexpr auto value() { return "keyboard_f6"; } };
      template<> struct key_name_t<0x40> { static constexpr auto value() { return "keyboard_f7"; } };
      template<> struct key_name_t<0x41> { static constexpr auto value() { return "keyboard_f8"; } };
      template<> struct key_name_t<0x42> { static constexpr auto value() { return "keyboard_f9"; } };
      template<> struct key_name_t<0x43> { static constexpr auto value() { return "keyboard_f10"; } };
      template<> struct key_name_t<0x44> { static constexpr auto value() { return "keyboard_f11"; } };
      template<> struct key_name_t<0x45> { static constexpr auto value() { return "keyboard_f12"; } };
      template<> struct key_name_t<0x46> { static constexpr auto value() { return "keyboard_print_screen"; } };
      template<> struct key_name_t<0x47> { static constexpr auto value() { return "keyboard_scroll_lock"; } };
      template<> struct key_name_t<0x48> { static constexpr auto value() { return "keyboard_pause"; } };
      template<> struct key_name_t<0x49> { static constexpr auto value() { return "keyboard_insert"; } };
      template<> struct key_name_t<0x4A> { static constexpr auto value() { return "keyboard_home"; } };
      template<> struct key_name_t<0x4B> { static constexpr auto value() { return "keyboard_page_up"; } };
      template<> struct key_name_t<0x4C> { static constexpr auto value() { return "keyboard_delete_forward"; } };
      template<> struct key_name_t<0x4D> { static constexpr auto value() { return "keyboard_end"; } };
      template<> struct key_name_t<0x4E> { static constexpr auto value() { return "keyboard_page_down"; } };
      template<> struct key_name_t<0x4F> { static constexpr auto value() { return "keyboard_right_arrow"; } };
      template<> struct key_name_t<0x50> { static constexpr auto value() { return "keyboard_left_arrow"; } };
      template<> struct key_name_t<0x51> { static constexpr auto value() { return "keyboard_down_arrow"; } };
      template<> struct key_name_t<0x52> { static constexpr auto value() { return "keyboard_up_arrow"; } };
      template<> struct key_name_t<0x53> { static constexpr auto value() { return "keypad_num_lock_and_clear"; } };
      template<> struct key_name_t<0x54> { static constexpr auto value() { return "keypad_slash"; } };
      template<> struct key_name_t<0x55> { static constexpr auto value() { return "keypad_asterisk"; } };
      template<> struct key_name_t<0x56> { static constexpr auto value() { return "keypad_minus"; } };
      template<> struct key_name_t<0x57> { static constexpr auto value() { return "keypad_plus"; } };
      template<> struct key_name_t<0x58> { static constexpr auto value() { return "keypad_enter"; } };
      template<> struct key_name_t<0x59> { static constexpr auto value() { return "keypad_1_and_end"; } };
      template<> struct key_name_t<0x5A> { static constexpr auto value() { return "keypad_2_and_down_arrow"; } };
      template<> struct key_name_t<0x5B> { static constexpr auto value() { return "keypad_3_and_page_dn"; } };
      template<> struct key_name_t<0x5C> { static constexpr auto value() { return "keypad_4_and_left_arrow"; } };
      template<> struct key_name_t<0x5D> { static constexpr auto value() { return "keypad_5"; } };
      template<> struct key_name_t<0x5E> { static constexpr auto value() { return "keypad_6_and_right_arrow"; } };
      template<> struct key_name_t<0x5F> { static constexpr auto value() { return "keypad_7_and_home"; } };
      template<> struct key_name_t<0x60> { static constexpr auto value() { return "keypad_8_and_up_arrow"; } };
      template<> struct key_name_t<0x61> { static constexpr auto value() { return "keypad_9_and_page_up"; } };
      template<> struct key_name_t<0x62> { static constexpr auto value() { return "keypad_0x_and_insert"; } };
      template<> struct key_name_t<0x63> { static constexpr auto value() { return "keypad_dot_and_delete"; } };
      template<> struct key_name_t<0x64> { static constexpr auto value() { return "keyboard_non_us_backslash_and_vertical_bar"; } };
      template<> struct key_name_t<0x65> { static constexpr auto value() { return "keyboard_application"; } };
      template<> struct key_name_t<0x66> { static constexpr auto value() { return "keyboard_power"; } };
      template<> struct key_name_t<0x67> { static constexpr auto value() { return "keypad_equal"; } };
      template<> struct key_name_t<0x68> { static constexpr auto value() { return "keyboard_f13"; } };
      template<> struct key_name_t<0x69> { static constexpr auto value() { return "keyboard_f14"; } };
      template<> struct key_name_t<0x6A> { static constexpr auto value() { return "keyboard_f15"; } };
      template<> struct key_name_t<0x6B> { static constexpr auto value() { return "keyboard_f16"; } };
      template<> struct key_name_t<0x6C> { static constexpr auto value() { return "keyboard_f17"; } };
      template<> struct key_name_t<0x6D> { static constexpr auto value() { return "keyboard_f18"; } };
      template<> struct key_name_t<0x6E> { static constexpr auto value() { return "keyboard_f19"; } };
      template<> struct key_name_t<0x6F> { static constexpr auto value() { return "keyboard_f20"; } };
      template<> struct key_name_t<0x70> { static constexpr auto value() { return "keyboard_f21"; } };
      template<> struct key_name_t<0x71> { static constexpr auto value() { return "keyboard_f22"; } };
      template<> struct key_name_t<0x72> { static constexpr auto value() { return "keyboard_f23"; } };
      template<> struct key_name_t<0x73> { static constexpr auto value() { return "keyboard_f24"; } };
      template<> struct key_name_t<0x74> { static constexpr auto value() { return "keyboard_execute"; } };
      template<> struct key_name_t<0x75> { static constexpr auto value() { return "keyboard_help"; } };
      template<> struct key_name_t<0x76> { static constexpr auto value() { return "keyboard_menu"; } };
      template<> struct key_name_t<0x77> { static constexpr auto value() { return "keyboard_select"; } };
      template<> struct key_name_t<0x78> { static constexpr auto value() { return "keyboard_stop"; } };
      template<> struct key_name_t<0x79> { static constexpr auto value() { return "keyboard_again"; } };
      template<> struct key_name_t<0x7A> { static constexpr auto value() { return "keyboard_undo"; } };
      template<> struct key_name_t<0x7B> { static constexpr auto value() { return "keyboard_cut"; } };
      template<> struct key_name_t<0x7C> { static constexpr auto value() { return "keyboard_copy"; } };
      template<> struct key_name_t<0x7D> { static constexpr auto value() { return "keyboard_paste"; } };
      template<> struct key_name_t<0x7E> { static constexpr auto value() { return "keyboard_find"; } };
      template<> struct key_name_t<0x7F> { static constexpr auto value() { return "keyboard_mute"; } };
      template<> struct key_name_t<0x80> { static constexpr auto value() { return "keyboard_volume_up"; } };
      template<> struct key_name_t<0x81> { static constexpr auto value() { return "keyboard_vokume_down"; } };
      template<> struct key_name_t<0x82> { static constexpr auto value() { return "keyboard_locking_caps_lock"; } };
      template<> struct key_name_t<0x83> { static constexpr auto value() { return "keyboard_locking_num_lock"; } };
      template<> struct key_name_t<0x84> { static constexpr auto value() { return "keyboard_locking_scroll_lock"; } };
      template<> struct key_name_t<0x85> { static constexpr auto value() { return "keypad_comma"; } };
      template<> struct key_name_t<0x86> { static constexpr auto value() { return "keypad_equal_sign"; } };
      template<> struct key_name_t<0x87> { static constexpr auto value() { return "keyboard_internatinal1"; } };
      template<> struct key_name_t<0x88> { static constexpr auto value() { return "keyboard_internatinal2"; } };
      template<> struct key_name_t<0x89> { static constexpr auto value() { return "keyboard_internatinal3"; } };
      template<> struct key_name_t<0x8A> { static constexpr auto value() { return "keyboard_internatinal4"; } };
      template<> struct key_name_t<0x8B> { static constexpr auto value() { return "keyboard_internatinal5"; } };
      template<> struct key_name_t<0x8C> { static constexpr auto value() { return "keyboard_internatinal6"; } };
      template<> struct key_name_t<0x8D> { static constexpr auto value() { return "keyboard_internatinal7"; } };
      template<> struct key_name_t<0x8E> { static constexpr auto value() { return "keyboard_internatinal8"; } };
      template<> struct key_name_t<0x8F> { static constexpr auto value() { return "keyboard_internatinal9"; } };
      template<> struct key_name_t<0x90> { static constexpr auto value() { return "keyboard_lang1"; } };
      template<> struct key_name_t<0x91> { static constexpr auto value() { return "keyboard_lang2"; } };
      template<> struct key_name_t<0x92> { static constexpr auto value() { return "keyboard_lang3"; } };
      template<> struct key_name_t<0x93> { static constexpr auto value() { return "keyboard_lang4"; } };
      template<> struct key_name_t<0x94> { static constexpr auto value() { return "keyboard_lang5"; } };
      template<> struct key_name_t<0x95> { static constexpr auto value() { return "keyboard_lang6"; } };
      template<> struct key_name_t<0x96> { static constexpr auto value() { return "keyboard_lang7"; } };
      template<> struct key_name_t<0x97> { static constexpr auto value() { return "keyboard_lang8"; } };
      template<> struct key_name_t<0x98> { static constexpr auto value() { return "keyboard_lang9"; } };
      template<> struct key_name_t<0x99> { static constexpr auto value() { return "keyboard_alternate_erase"; } };
      template<> struct key_name_t<0x9A> { static constexpr auto value() { return "keyboard_sysreq_attention"; } };
      template<> struct key_name_t<0x9B> { static constexpr auto value() { return "keyboard_cancel"; } };
      template<> struct key_name_t<0x9C> { static constexpr auto value() { return "keyboard_clear"; } };
      template<> struct key_name_t<0x9D> { static constexpr auto value() { return "keyboard_prior"; } };
      template<> struct key_name_t<0x9E> { static constexpr auto value() { return "keyboard_return"; } };
      template<> struct key_name_t<0x9F> { static constexpr auto value() { return "keyboard_separator"; } };
      template<> struct key_name_t<0xA0> { static constexpr auto value() { return "keyboard_out"; } };
      template<> struct key_name_t<0xA1> { static constexpr auto value() { return "keyboard_oper"; } };
      template<> struct key_name_t<0xA2> { static constexpr auto value() { return "keyboard_clear_again"; } };
      template<> struct key_name_t<0xA3> { static constexpr auto value() { return "keyboard_cr_sel_props"; } };
      template<> struct key_name_t<0xA4> { static constexpr auto value() { return "keyboard_ex_sel"; } };
      
      template<> struct key_name_t<0xB0> { static constexpr auto value() { return "keypad_00"; } };
      template<> struct key_name_t<0xB1> { static constexpr auto value() { return "keypad_000"; } };
      template<> struct key_name_t<0xB2> { static constexpr auto value() { return "thousands_separator"; } };
      template<> struct key_name_t<0xB3> { static constexpr auto value() { return "decimal_secparator"; } };
      template<> struct key_name_t<0xB4> { static constexpr auto value() { return "currency_unit"; } };
      template<> struct key_name_t<0xB5> { static constexpr auto value() { return "currency_sub_unit"; } };
      template<> struct key_name_t<0xB6> { static constexpr auto value() { return "keypad_round_bracket_open"; } };
      template<> struct key_name_t<0xB7> { static constexpr auto value() { return "keypad_round_bracket_close"; } };
      template<> struct key_name_t<0xB8> { static constexpr auto value() { return "keypad_curly_bracket_open"; } };
      template<> struct key_name_t<0xB9> { static constexpr auto value() { return "keypad_curly_bracket_close"; } };
      template<> struct key_name_t<0xBA> { static constexpr auto value() { return "keypad_tab"; } };
      template<> struct key_name_t<0xBB> { static constexpr auto value() { return "keypad_backspace"; } };
      template<> struct key_name_t<0xBC> { static constexpr auto value() { return "keypad_a"; } };
      template<> struct key_name_t<0xBD> { static constexpr auto value() { return "keypad_b"; } };
      template<> struct key_name_t<0xBE> { static constexpr auto value() { return "keypad_c"; } };
      template<> struct key_name_t<0xBF> { static constexpr auto value() { return "keypad_d"; } };
      template<> struct key_name_t<0xC0> { static constexpr auto value() { return "keypad_e"; } };
      template<> struct key_name_t<0xC1> { static constexpr auto value() { return "keypad_f"; } };
      template<> struct key_name_t<0xC2> { static constexpr auto value() { return "keypad_xor"; } };
      template<> struct key_name_t<0xC3> { static constexpr auto value() { return "keypad_hat"; } };
      template<> struct key_name_t<0xC4> { static constexpr auto value() { return "keypad_parcent"; } };
      template<> struct key_name_t<0xC5> { static constexpr auto value() { return "keypad_left_angle_bracket"; } };
      template<> struct key_name_t<0xC6> { static constexpr auto value() { return "keypad_right_aangle_bracket"; } };
      template<> struct key_name_t<0xC7> { static constexpr auto value() { return "keypad_and"; } };
      template<> struct key_name_t<0xC8> { static constexpr auto value() { return "keypad_and_and"; } };
      template<> struct key_name_t<0xC9> { static constexpr auto value() { return "keypad_virtical_bar"; } };
      template<> struct key_name_t<0xCA> { static constexpr auto value() { return "keypad_virtical_bar_virtical_bar"; } };
      template<> struct key_name_t<0xCB> { static constexpr auto value() { return "keypad_colon"; } };
      template<> struct key_name_t<0xCC> { static constexpr auto value() { return "keypad_number"; } };
      template<> struct key_name_t<0xCD> { static constexpr auto value() { return "keypad_space"; } };
      template<> struct key_name_t<0xCE> { static constexpr auto value() { return "keypad_exclamation"; } };
      template<> struct key_name_t<0xCF> { static constexpr auto value() { return "keypad_memory_store"; } };
      template<> struct key_name_t<0xD0> { static constexpr auto value() { return "keypad_memory_recall"; } };
      template<> struct key_name_t<0xD1> { static constexpr auto value() { return "keypad_memory_clear"; } };
      template<> struct key_name_t<0xD2> { static constexpr auto value() { return "keypad_memory_add"; } };
      template<> struct key_name_t<0xD3> { static constexpr auto value() { return "keypad_memory_subtract"; } };
      template<> struct key_name_t<0xD4> { static constexpr auto value() { return "keypad_memory_multiply"; } };
      template<> struct key_name_t<0xD5> { static constexpr auto value() { return "keypad_memory_divide"; } };
      template<> struct key_name_t<0xD6> { static constexpr auto value() { return "keypad_plus_minus"; } };
      template<> struct key_name_t<0xD7> { static constexpr auto value() { return "keypad_clear"; } };
      template<> struct key_name_t<0xD8> { static constexpr auto value() { return "keypad_clear_entry"; } };
      template<> struct key_name_t<0xD9> { static constexpr auto value() { return "keypad_binary"; } };
      template<> struct key_name_t<0xDA> { static constexpr auto value() { return "keypad_octal"; } };
      template<> struct key_name_t<0xDB> { static constexpr auto value() { return "keypad_decimal"; } };
      template<> struct key_name_t<0xDC> { static constexpr auto value() { return "keypad_hexadecimal"; } };
      
      template<> struct key_name_t<0xE0> { static constexpr auto value() { return "keyboard_left_control"; } };
      template<> struct key_name_t<0xE1> { static constexpr auto value() { return "keyboard_left_shift"; } };
      template<> struct key_name_t<0xE2> { static constexpr auto value() { return "keyboard_left_alt"; } };
      template<> struct key_name_t<0xE3> { static constexpr auto value() { return "keyboard_left_gui"; } };
      template<> struct key_name_t<0xE4> { static constexpr auto value() { return "keyboard_right_control"; } };
      template<> struct key_name_t<0xE5> { static constexpr auto value() { return "keyboard_right_shift"; } };
      template<> struct key_name_t<0xE6> { static constexpr auto value() { return "keyboard_right_alt"; } };
      template<> struct key_name_t<0xE7> { static constexpr auto value() { return "keyboard_right_gui"; } };
      
      // easy for use
      using key = key_t;
      template<key_code_t T_keycode> using key_name = key_name_t<T_keycode>;
    }
  }
}