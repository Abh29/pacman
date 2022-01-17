# Sie dürfen Regeln in dieser Datei hinzufügen, aber nicht entfernen.  			 		   					  	    		 	   	   			  	 	 	  		  					     	 	   				 	  		  		
CFLAGS_FSANITIZE := -g -std=c99 -Wall -Wextra -Werror -Werror=vla -Og -Wmissing-prototypes -fsanitize=address -fsanitize=undefined
CFLAGS_VALGRIND  := -g -std=c99 -Wall -Wextra -Werror -Werror=vla -Og -Wmissing-prototypes

# Hier können weitere Dateien hinzugefügt werden, wie zum Beispiel	 				     	 	  	  	 	 	     	 	 			      	 						 		  	   		   		     	 				 		
# SOURCES := pacman.c ghost.c oder HEADERS := pacman.h ghost.h 		  		  		       	 	  			   			 		 		 				 	 			   	 						 	 					 	 	  					 
SOURCES := pacman.c
HEADERS := pacman.h

run: test_output test_arguments codestyle checksums misc mytests

pacman_fsanitize: $(SOURCES) $(HEADERS)
	gcc $(CFLAGS_FSANITIZE) $(SOURCES) -o pacman_fsanitize -pthread -lm

pacman_valgrind: $(SOURCES) $(HEADERS)
	gcc $(CFLAGS_VALGRIND) $(SOURCES) -o pacman_valgrind -pthread -lm

test_output: pacman_fsanitize
	tests/test_output.sh

test: tests/test.sh
	tests/test.sh

test_arguments_fsanitize: pacman_fsanitize
	tests/test_arguments.sh fsanitize

test_arguments_valgrind: pacman_valgrind
	tests/test_arguments.sh valgrind

test_arguments: test_arguments_fsanitize test_arguments_valgrind

misc:
	tests/check_misc.py

codestyle:
	tests/codestyle.py

checksums:
	tests/check_checksums.sh

mytests:
	# Sie müssen eigene Tests erstellen. Dabei müssen Sie mindestens 2 oder   				 		  	  		  	  	  		 	  	  	   	  		  	  			 		   			 		  	 	 		    	 	  
	# gerne auch mehr "Dinge" testen, die Sie sich selber aussuchen dürfen. 	 				    	 			 	   	 	      		   		 	  			  	 					  	   	   	 				   					  	
	# Erstellen Sie Regeln zum Kompilieren und ausführen der Tests.    	   	 	 			 	 				    	 		   	    			 		       	 		     				  	     				   	
	# Beschreiben Sie hier kurz, was sie testen:     		   	 	     		 		  	 		 	 	      	  		 		 	  	 		 	  		   	 			 	 			     
	# Test 1:		 				 				   	 		       	  			 			   		   			 	  	 					 	  					  	 	 	 	 			
	# (Beispiel) Ich teste, ob Pac-Man nicht durch Wände laufen kann. 		 		  	  						 	 		 	 		  	 	  				 	    	 	     	 			   	 	   	     		   			
	# Test 2:		 	 			 	  			   			 	 				 	 		 			 		 				        		 	 	  				    	       	 	
	# ...	 	  	 				 		 	  			 		  		        					  			 		  		 		 	  	  	   	 		   		 		 
	./FEHLER_Sie_haben_noch_keine_eigenen_Tests_erstellt
