//
// Simple calculator
//
// How to build:
//   g++ -o calc calc.cpp `pkg-config -libs --cflags gtk+-3.0`
//

#include <string>
#include <gtk/gtk.h>

enum operation_e { CLEAR, ADD, SUBTRACT, MULTIPLY, DIVIDE } operation = CLEAR ;

double acc = 0.0;

static void
push_button ( GtkButton *widget,
              gpointer   data )
{
  GtkLabel *value = GTK_LABEL( data );

  const gchar* label = gtk_button_get_label( widget );
  g_print( "%s\n", label );

  std::string w = label;
  if( w[0] == '.' ) {
    const gchar* v = gtk_label_get_label( value );
    std::string s = v;
    bool has_decimal = false;
    for( auto c : s ) {
      if( c == '.' ) {
        has_decimal = true;
        break;
      }
    }
    if( !has_decimal ) {
      std::string s = v + w;
      gtk_label_set_label( value, s.c_str() );
    }
  } else if( std::isdigit( w[0] ) ) {
    const gchar* v = gtk_label_get_label( value );
    std::string s = v + w;
    gtk_label_set_label( value, s.c_str() );
  } else if( w[0] == '+' ) {
    operation = ADD;
    const gchar* v = gtk_label_get_label( value );
    acc = std::atof( v );
    gtk_label_set_label( value, "" );
  } else if( w[0] == '-' ) {
    operation = SUBTRACT;
    const gchar* v = gtk_label_get_label( value );
    acc = std::atof( v );
    gtk_label_set_label( value, "" );
  } else if( w[0] == '/' ) {
    operation = DIVIDE;
    const gchar* v = gtk_label_get_label( value );
    acc = std::atof( v );
    gtk_label_set_label( value, "" );
  } else if( w[0] == '*' ) {
    operation = MULTIPLY;
    const gchar* v = gtk_label_get_label( value );
    acc = std::atof( v );
    gtk_label_set_label( value, "" );
  } else if( w[0] == 'C' ) {
    operation = CLEAR;
    acc = 0.0;
    gtk_label_set_label( value, "" );
  } else if( w[0] == 'E' ) {
    const gchar* v = gtk_label_get_label( value );
    double operand = std::atof( v );
    switch( operation ) {
      case ADD: acc += operand; break;
      case SUBTRACT: acc -= operand; break;
      case MULTIPLY: acc *= operand; break;
      case DIVIDE: acc /= operand; break;
      case CLEAR: acc = 0.0; break;
    }
    std::string s = std::to_string( acc );
    gtk_label_set_label( value, s.c_str() );
  }
}

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Calc");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  GtkWidget *grid;
  grid = gtk_grid_new();
  gtk_grid_set_row_homogeneous( GTK_GRID( grid ), true );
  gtk_grid_set_column_homogeneous( GTK_GRID( grid ), true );
  
  GtkWidget *value;
  value = gtk_label_new( "" );
  gtk_grid_attach( GTK_GRID( grid ), value, 0, 5, 4, 1 );

  GtkWidget *period;
  period = gtk_button_new_with_label( "." );
  g_signal_connect( period, "clicked", G_CALLBACK( push_button ), value );
  gtk_grid_attach( GTK_GRID( grid ), period, 2, 4, 1, 1 );

  GtkWidget *numbers[10];
  numbers[ 0 ] = gtk_button_new_with_label( "0" );
  g_signal_connect( numbers[ 0 ], "clicked", G_CALLBACK( push_button ), value );
  gtk_grid_attach( GTK_GRID( grid ), numbers[ 0 ], 0, 4, 2, 1 );

  numbers[ 1 ] = gtk_button_new_with_label( "1" );
  g_signal_connect( numbers[ 1 ], "clicked", G_CALLBACK( push_button ), value );
  gtk_grid_attach( GTK_GRID( grid ), numbers[ 1 ], 0, 3, 1, 1 );

  numbers[ 2 ] = gtk_button_new_with_label( "2" );
  g_signal_connect( numbers[ 2 ], "clicked", G_CALLBACK( push_button ), value );
  gtk_grid_attach( GTK_GRID( grid ), numbers[ 2 ], 1, 3, 1, 1 );

  numbers[ 3 ] = gtk_button_new_with_label( "3" );
  g_signal_connect( numbers[ 3 ], "clicked", G_CALLBACK( push_button ), value );
  gtk_grid_attach( GTK_GRID( grid ), numbers[ 3 ], 2, 3, 1, 1 );

  numbers[ 4 ] = gtk_button_new_with_label( "4" );
  g_signal_connect( numbers[ 4 ], "clicked", G_CALLBACK( push_button ), value );
  gtk_grid_attach( GTK_GRID( grid ), numbers[ 4 ], 0, 2, 1, 1 );

  numbers[ 5 ] = gtk_button_new_with_label( "5" );
  g_signal_connect( numbers[ 5 ], "clicked", G_CALLBACK( push_button ), value );
  gtk_grid_attach( GTK_GRID( grid ), numbers[ 5 ], 1, 2, 1, 1 );

  numbers[ 6 ] = gtk_button_new_with_label( "6" );
  g_signal_connect( numbers[ 6 ], "clicked", G_CALLBACK( push_button ), value );
  gtk_grid_attach( GTK_GRID( grid ), numbers[ 6 ], 2, 2, 1, 1 );

  numbers[ 7 ] = gtk_button_new_with_label( "7" );
  g_signal_connect( numbers[ 7 ], "clicked", G_CALLBACK( push_button ), value );
  gtk_grid_attach( GTK_GRID( grid ), numbers[ 7 ], 0, 1, 1, 1 );

  numbers[ 8 ] = gtk_button_new_with_label( "8" );
  g_signal_connect( numbers[ 8 ], "clicked", G_CALLBACK( push_button ), value );
  gtk_grid_attach( GTK_GRID( grid ), numbers[ 8 ], 1, 1, 1, 1 );

  numbers[ 9 ] = gtk_button_new_with_label( "9" );
  g_signal_connect( numbers[ 9 ], "clicked", G_CALLBACK( push_button ), value );
  gtk_grid_attach( GTK_GRID( grid ), numbers[ 9 ], 2, 1, 1, 1 );

  GtkWidget *enter;
  enter = gtk_button_new_with_label( "Enter" );
  //gtk_label_set_angle( GTK_LABEL( enter ), 270 );
  g_signal_connect( enter, "clicked", G_CALLBACK( push_button ), value );
  gtk_grid_attach( GTK_GRID( grid ), enter, 3, 3, 1, 2 );

  GtkWidget *plus;
  plus = gtk_button_new_with_label( "+" );
  g_signal_connect( plus, "clicked", G_CALLBACK( push_button ), value );
  gtk_grid_attach( GTK_GRID( grid ), plus, 3, 1, 1, 2 );

  GtkWidget *minus;
  minus = gtk_button_new_with_label( "-" );
  g_signal_connect( minus, "clicked", G_CALLBACK( push_button ), value );
  gtk_grid_attach( GTK_GRID( grid ), minus, 3, 0, 1, 1 );

  GtkWidget *mult;
  mult = gtk_button_new_with_label( "*" );
  g_signal_connect( mult, "clicked", G_CALLBACK( push_button ), value );
  gtk_grid_attach( GTK_GRID( grid ), mult, 2, 0, 1, 1 );
  
  GtkWidget *div;
  div = gtk_button_new_with_label( "/" );
  g_signal_connect( div, "clicked", G_CALLBACK( push_button ), value );
  gtk_grid_attach( GTK_GRID( grid ), div, 1, 0, 1, 1 );
  
  GtkWidget *clear;
  clear = gtk_button_new_with_label( "C" );
  g_signal_connect( clear, "clicked", G_CALLBACK( push_button ), value );
  gtk_grid_attach( GTK_GRID( grid ), clear, 0, 0, 1, 1 );
  

  gtk_container_add( GTK_CONTAINER( window ), grid );

  gtk_widget_show_all( window );
}

int
main( int    argc,
      char **argv )
{
  GtkApplication *app;
  int status;

  app = gtk_application_new( "org.gtk.example", G_APPLICATION_FLAGS_NONE );
  g_signal_connect( app, "activate", G_CALLBACK (activate), NULL );
  status = g_application_run( G_APPLICATION( app ), argc, argv );
  g_object_unref( app );

  return status;
}
