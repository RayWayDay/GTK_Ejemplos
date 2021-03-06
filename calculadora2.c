#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct def_Nodo
{
  GtkWidget *button;
  char Signo[2];
  float Num;
} TipoNodo;

GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox);
GtkWidget *AddButtonBlue(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox);
GtkWidget *AddButtonGray(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox);
void InsertarCampo(GtkButton *button, gpointer data);
void Leer_Arch(GtkButton *button, gpointer data);
void BorrarCampo(GtkButton *button, gpointer data);
void Operacion(GtkButton *button, gpointer data);
void BorraNum(GtkButton *button, gpointer data);
void MostrarResultado(GtkButton *button, gpointer data);
void StopTheApp(GtkWidget *window, gpointer data);
void Imprimir(GtkButton *button, gpointer data);


gint main ( gint argc, gchar *argv[])
{

  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *horizontalbox;
  GtkWidget *verticalbox;
  GtkWidget *entrybox;

  gtk_init(&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),300,400);
  gtk_container_border_width(GTK_CONTAINER(window),7);


  verticalbox = gtk_vbox_new(TRUE,5);

  entrybox = gtk_entry_new();

  horizontalbox = gtk_hbox_new(TRUE,5);

  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox,TRUE,TRUE,0);

  button = AddButtonBlue(horizontalbox,"CE",BorrarCampo,entrybox);
  button = AddButtonBlue(horizontalbox,"C",BorraNum,entrybox);
  button = AddButtonBlue(horizontalbox,"%",Operacion,entrybox);
  button = AddButtonBlue(horizontalbox,"/",Operacion,entrybox);
  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);
  horizontalbox = gtk_hbox_new(TRUE,5);


  button = AddButton(horizontalbox,"7",InsertarCampo,entrybox);
  button = AddButton(horizontalbox,"8",InsertarCampo,entrybox);
  button = AddButton(horizontalbox,"9",InsertarCampo,entrybox);
  button = AddButton(horizontalbox,"x",Operacion,entrybox);
  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);
  horizontalbox = gtk_hbox_new(TRUE,5);

  button = AddButton(horizontalbox,"4",InsertarCampo,entrybox);
  button = AddButton(horizontalbox,"5",InsertarCampo,entrybox);
  button = AddButton(horizontalbox,"6",InsertarCampo,entrybox);
  button = AddButton(horizontalbox,"+",Operacion,entrybox);
  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);
  horizontalbox = gtk_hbox_new(TRUE,5);

  button = AddButton(horizontalbox,"1",InsertarCampo,entrybox);
  button = AddButton(horizontalbox,"2",InsertarCampo,entrybox);
  button = AddButton(horizontalbox,"3",InsertarCampo,entrybox);
  button = AddButton(horizontalbox,"-",Operacion,entrybox);
  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);
  horizontalbox = gtk_hbox_new(TRUE,5);

  button = AddButtonGray(horizontalbox,"0",InsertarCampo,entrybox);
  button = AddButtonGray(horizontalbox,".",InsertarCampo,entrybox);
  button = AddButtonGray(horizontalbox,"=",MostrarResultado,entrybox);
  gtk_box_pack_start(GTK_BOX(verticalbox),horizontalbox,TRUE,TRUE,0);

  // Empaqueto en la caja principal / vertical la entrada de texto.



  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);


  gtk_container_add(GTK_CONTAINER(window),verticalbox);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;

}



GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox)
{
    GtkWidget *button;
    button = gtk_button_new_with_label(buttonText);
    gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CallBackFunction),EntryBox);
    gtk_widget_show(button);
    return button;
}

GtkWidget *AddButtonBlue(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox)
{
    GtkWidget *button;
    GdkColor color;
    gdk_color_parse("#5B6168",&color);
    button = gtk_button_new_with_label(buttonText);
    gtk_widget_modify_bg(button,GTK_STATE_NORMAL,&color);
    gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CallBackFunction),EntryBox);
    gtk_widget_show(button);
    return button;
}

GtkWidget *AddButtonGray(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox)
{
    GtkWidget *button;
    GdkColor color;
    gdk_color_parse("#1D87FF",&color);
    button = gtk_button_new_with_label(buttonText);
    gtk_widget_modify_bg(button,GTK_STATE_NORMAL,&color);
    gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CallBackFunction),EntryBox);
    gtk_widget_show(button);
    return button;
}

void InsertarCampo(GtkButton *button, gpointer data)
{
  const gchar *Etiqueta;
  Etiqueta = gtk_button_get_label(button);
  gtk_entry_append_text(GTK_ENTRY(data),Etiqueta);
}

void BorrarCampo(GtkButton *button, gpointer data)
{
  gtk_entry_set_text(GTK_ENTRY(data)," ");
}

void BorraNum(GtkButton *button, gpointer data)
{
  char Nuevo[100];
  const gchar *Entrada;
  Entrada =gtk_entry_get_text(GTK_ENTRY(data));
  strcpy(Nuevo,Entrada);
  Nuevo[strlen(Nuevo)-1]='\0';
  gtk_entry_set_text(GTK_ENTRY(data),Nuevo);
}

void Operacion(GtkButton *button, gpointer data)
{
  TipoNodo *datos=(TipoNodo *)data;
  const gchar *Entrada,*Operacion;
  Entrada =gtk_entry_get_text(GTK_ENTRY(data));
  Operacion = gtk_button_get_label(button);
  datos->Num =  atof(Entrada);
  strcpy(datos->Signo,Operacion);
  gtk_entry_set_text(GTK_ENTRY(data)," ");
}

void MostrarResultado(GtkButton *button, gpointer data)
{
  char Resultado[100];
  float Res;
  int temp;
  TipoNodo *datos=(TipoNodo *)data;
  const gchar *Entrada;
  Entrada =gtk_entry_get_text(GTK_ENTRY(data));
  switch(datos -> Signo[0])
  {
    case '+':
      Res= datos -> Num + atof(Entrada);
    break;
    case '-':
      Res= datos -> Num - atof(Entrada);
    break;
    case 'x':
      Res= datos -> Num * atof(Entrada);
    break;
    case '/':
      Res= datos -> Num / atof(Entrada);
    break;
    case '%':
      temp = datos -> Num;
      Res= temp % atoi(Entrada);
    break;
  }
  sprintf(Resultado,"%.3f",Res);
  gtk_entry_set_text(GTK_ENTRY(data),Resultado);
}

void StopTheApp(GtkWidget *window, gpointer data)
{
    gtk_main_quit();
}
