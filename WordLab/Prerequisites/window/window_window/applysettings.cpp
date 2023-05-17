void window::applysettings(){
	for(int n=0;n<text.capacity();++n){
		if(strstr(text.line(n),"#line ")==text.line(n)&&strlen(text.line(n))>5){
			if(!text.iscmd[n]){
				text.iscmd[n]=1;
				if(strchr("+-",text.line(n)[5])) n+=atoi(text.line(n)+5);
				else n=atoi(text.line(n)+5);
			}
		}else if(strstr(text.line(n),"#linesize ")==text.line(n)&&text.length(n)>strlen("#linesize ")+1){
			if(!text.iscmd[n]){
				text.iscmd[n] = 1;
				text._ColMax = atoi(text.line(n)+strlen("#linesize "));
				int num_line = text.size();
				char ** copy;
				bool * iscmd;
				copy = (char **) calloc(sizeof(char*),text.capacity());
				iscmd = (bool *) calloc(sizeof(bool),text.capacity());
				for(int i=0;i<num_line;++i){
					copy[i] = (char*) calloc(sizeof(char),text.linecapacity());
					strcpy( copy[i],text.line(i) );
					iscmd[i] = text.iscmd[i];
				}
				text._alloc();
				for(int i=0;i<num_line;++i){
					strcpy( text.line(i),copy[i] );
					free(copy[i]);
					text.iscmd[i] = iscmd[i];
				}
				free(iscmd);
				free(copy);
				text.setsize(num_line);
			}
		}else if(strstr(text.line(n),"#newpage#")==text.line(n)){
			if(!text.iscmd[n]){
				text._alloc();
				text.setsize(0);
				n=0;
			}
		}else if(strstr(text.line(n),"#launch ")==text.line(n)){
			if (!text.iscmd[n]) {
				text.iscmd[n] = 1;
				launch(text.line(n) + strlen("#launch "));
			}
		}else if(strstr(text.line(n),"#left")==text.line(n)){
			if(!text.iscmd[n]){
				text.iscmd[n]=1;
				margin.left += atoi(text.line(n)+5);
				limit(margin.left,margin.left,0,ScreenX-margin.right);
			}
		}else if(strstr(text.line(n),"#right")==text.line(n)){
			if(!text.iscmd[n]){
				text.iscmd[n]=1;
				margin.right += atoi(text.line(n)+6);
				limit(margin.right,margin.right,0,ScreenX-margin.left);
			}
		}else if(strstr(text.line(n),"#top")==text.line(n)){
			if(!text.iscmd[n]){
				text.iscmd[n]=1;
				margin.top += atoi(text.line(n)+4);
				limit(margin.top,margin.top,0,ScreenY-margin.bottom);
			}
		}else if(strstr(text.line(n),"#bottom")==text.line(n)){
			if(!text.iscmd[n]){
				text.iscmd[n]=1;
				margin.bottom += atoi(text.line(n)+7);
				limit(margin.bottom,margin.bottom,0,ScreenY-margin.top);
			}
		}else if(strstr(text.line(n),"#color.text.content=")){
			if(!text.iscmd[n]){
				text.iscmd[n]=1;
				color[WINDOW_STATUS::active].text[0].content = text.line(n)+strlen("#color.text.content=");
				color[WINDOW_STATUS::active].text[1].content = text.line(n)+strlen("#color.text.content=");
			}
		}else if(strstr(text.line(n),"#color.text.background=")){
			if(!text.iscmd[n]){
				text.iscmd[n]=1;
				color[WINDOW_STATUS::active].text[0].background = text.line(n)+strlen("#color.text.background=");
				color[WINDOW_STATUS::active].text[1].background = text.line(n)+strlen("#color.text.background=");
			}
		}else if(strstr(text.line(n),"#color.text[0].content=")){
			if(!text.iscmd[n]){
				text.iscmd[n]=1;
				color[WINDOW_STATUS::active].text[0].content = text.line(n)+strlen("#color.text[0].content=");
			}
		}else if(strstr(text.line(n),"#color.text[0].background=")){
			if(!text.iscmd[n]){
				text.iscmd[n]=1;
				color[WINDOW_STATUS::active].text[0].background = text.line(n)+strlen("#color.text[0].background=");
			}
		}else if(strstr(text.line(n),"#color.text[1].content=")){
			if(!text.iscmd[n]){
				text.iscmd[n]=1;
				color[WINDOW_STATUS::active].text[1].content = text.line(n)+strlen("#color.text[1].content=");
			}
		}else if(strstr(text.line(n),"#color.text[1].background=")){
			if(!text.iscmd[n]){
				text.iscmd[n]=1;
				color[WINDOW_STATUS::active].text[1].background = text.line(n)+strlen("#color.text[1].background=");
			}
		}else if(strstr(text.line(n),"#color.padding.background=")){
			if(!text.iscmd[n]){
				text.iscmd[n]=1;
				color[WINDOW_STATUS::active].padding.background = text.line(n)+strlen("#color.padding.background=");
			}
		}else if(strstr(text.line(n),"#color.padding.content=")){
			if(!text.iscmd[n]){
				text.iscmd[n]=1;
				color[WINDOW_STATUS::active].padding.content = text.line(n)+strlen("#color.padding.content=");
			}
		}else text.iscmd[n]=0;
	}
}
