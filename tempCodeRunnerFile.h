        if(ch == 13){
            if (Field[field_column][field_row].visited == 0)
                {
                    Field[field_column][field_row].visited = 1;
                    if(Field[field_column][field_row].area!=-1){
                        x_position = 2 ; 
                        y_position = 4 ;
                        running_arrowkey = false;
                        if(round){
                            round = false ; 
                        }
                        else {
                            round = true ; 
                        }
                    }
                    else {
                        if(round){
                            players_status[true] = players_status[true]+1 ; 
                        }
                        else {
                            players_status[false] = players_status[false]+1 ; 
                        }
                    }
                    
                }
                std::cout << "done" ; 
        }