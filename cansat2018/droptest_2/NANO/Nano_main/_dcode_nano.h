enum state {
  on_air=0,
  deploy,
  landing,
  wait_for_cut,
  wire_cutting,
  requests_gps,
  run_to_pos,
  on_position,
  wait_for_drill,
  drilling,
  read_probe,
  sending_probe,
  idle
};

enum MODE {
  Landing = 0xBA,GoingSite,Drill_Process,FINISHED
};

String decode_cmd(int code)
{
  String tempS="";
  switch (code)
  { 
    //MODE L
    case Landing:
      tempS += "Landing mode";
      break;
    case on_air:
      tempS += "on_air";
      break;
    case deploy:
      tempS += "deploy";
      break;
    case landing:
      tempS += "landing";
      break;
    case wait_for_cut:
      tempS += "wait_for_cut";
      break;
    case wire_cutting:
      tempS += "wire_cutting";
      break;

    //MODE G
    case GoingSite:
      tempS += "GoingSite mode";
      break;
    case requests_gps:
      tempS += "requests_gps";
      break;
    case run_to_pos:
      tempS += "run_to_pos";
      break;
    case on_position:
      tempS += "on_position";
      break;
    
    //mode D
    case Drill_Process:
      tempS += "Drilling mode";
      break;
    case wait_for_drill:
      tempS += "wait_for_drill";
      break;
    case drilling:
      tempS += "drilling";
      break;
    case read_probe:
      tempS += "read_probe";
      break;
    case sending_probe:
      tempS += "sending_probe";
      break;

    //SUCCESS
    case FINISHED:
      tempS += "FINISHED MODE";
      break;
    case idle:
      tempS += "idle";
      break;

    default: return "0";
  }
  return tempS;
}