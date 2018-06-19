void forward_tracking() {
  if (ls_condition == 0 ) {
    M_forward();
  } else if (ls_condition == 1) {
    M_right_slow();
  } else if (ls_condition == 2) {
    M_left_slow();
  } else if (ls_condition == 3) {
    M_right_fast();
  } else if (ls_condition == 4) {
    M_left_fast();
  } else if (ls_condition == 5) {//十字路口
    toggle_record = false;
    toggle_tracking = false;
  } else if (ls_condition == 6) {
    M_forward();
  }
}


void backward_tracking() {
  if (ls_condition == 0 ) {
    M_backward();
  } else if (ls_condition == 1) {
    M_back_right_fast();
  } else if (ls_condition == 2) {
    M_back_left_fast();
  } else if (ls_condition == 3) {
    M_back_right_fast();
  } else if (ls_condition == 4) {
    M_back_left_fast();
  } else if (ls_condition == 5) {//十字路口
    toggle_record = false;
    toggle_tracking = false;
  } else if (ls_condition == 6) {
    M_backward();
  }
}
