#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para representar un producto
typedef struct {
    int codigo;
    char nombre[100];
    int cantidad;
    float precio_bs;
    float precio_pesos;
    float precio_dolares;
    float precio_euros;
} Producto;

// Estructura para representar un cliente
typedef struct {
    char nombre[100];
    char apellido[100];
    char cedula[20];
    char telefono[20];
    char direccion[200];
} Cliente;

// Estructura para representar un ítem de factura
typedef struct {
    int codigo_producto;
    int cantidad;
    float precio_unitario;
} ItemFactura;

// Estructura para representar una factura
typedef struct {
    char fecha[20];
    char cedula_cliente[20];
    GList *items; // Lista de ítems de la factura
    float subtotal;
    float iva;
    float total;
} Factura;

// Estructura para representar una caja
typedef struct {
    int numero_caja;
    char responsable[100];
    float total_bs;
    float total_pesos;
    float total_dolares;
    float total_euros;
} Caja;

// Estructura para representar un trabajador
typedef struct {
    char nombre[100];
    char apellido[100];
    char cedula[20];
    char numero_trabajador[20];
    char telefono[20];
    char direccion[200];
} Trabajador;

// Listas globales para almacenar productos, clientes, facturas y cajas
GList *productos = NULL;
GList *clientes = NULL;
GList *facturas = NULL;
GList *cajas = NULL;
GList *trabajadores = NULL;

// Declaraciones de funciones
void on_crear_producto_clicked(GtkButton *button, gpointer user_data);
void on_modificar_producto_clicked(GtkButton *button, gpointer user_data);
void on_eliminar_producto_clicked(GtkButton *button, gpointer user_data);
void on_mostrar_productos_clicked(GtkButton *button, gpointer user_data);
void on_crear_cliente_clicked(GtkButton *button, gpointer user_data);
void on_modificar_cliente_clicked(GtkButton *button, gpointer user_data);
void on_eliminar_cliente_clicked(GtkButton *button, gpointer user_data);
void on_mostrar_clientes_clicked(GtkButton *button, gpointer user_data);
void on_crear_factura_clicked(GtkButton *button, gpointer user_data);
void on_modificar_factura_clicked(GtkButton *button, gpointer user_data);
void on_eliminar_factura_clicked(GtkButton *button, gpointer user_data);
void on_mostrar_facturas_clicked(GtkButton *button, gpointer user_data);
void on_productos_clicked(GtkButton *button, gpointer user_data);
void on_clientes_clicked(GtkButton *button, gpointer user_data);
void on_facturas_clicked(GtkButton *button, gpointer user_data);
void on_crear_factura_guardar(GtkButton *button, gpointer user_data);
void on_ventas_clicked(GtkButton *button, gpointer user_data);
void on_mostrar_ventas_diarias_clicked(GtkButton *button, gpointer user_data);
void on_mostrar_ventas_semanales_clicked(GtkButton *button, gpointer user_data);
void on_mostrar_ventas_mensuales_clicked(GtkButton *button, gpointer user_data);
void on_control_cajas_clicked(GtkButton *button, gpointer user_data);
void on_crear_caja_clicked(GtkButton *button, gpointer user_data);
void on_modificar_caja_clicked(GtkButton *button, gpointer user_data);
void on_eliminar_caja_clicked(GtkButton *button, gpointer user_data);
void on_mostrar_cajas_clicked(GtkButton *button, gpointer user_data);
void on_trabajadores_clicked(GtkButton *button, gpointer user_data);
void on_crear_trabajador_clicked(GtkButton *button, gpointer user_data);
void on_modificar_trabajador_clicked(GtkButton *button, gpointer user_data);
void on_eliminar_trabajador_clicked(GtkButton *button, gpointer user_data);
void on_mostrar_trabajadores_clicked(GtkButton *button, gpointer user_data);
void on_reportes_clicked(GtkButton *button, gpointer user_data);
void on_clientes_compras_clicked(GtkButton *button, gpointer user_data);
void on_productos_mas_vendidos_clicked(GtkButton *button, gpointer user_data);
void on_ultimas_facturas_clicked(GtkButton *button, gpointer user_data);
void on_cantidad_trabajadores_clicked(GtkButton *button, gpointer user_data);
void on_total_vendido_clicked(GtkButton *button, gpointer user_data);

// Función principal
int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button_productos, *button_clientes, *button_facturas;
    GtkWidget *button_ventas, *button_control_cajas, *button_trabajadores, *button_reportes;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear la ventana principal
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hipermercado Cachamay");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Botón para el módulo de productos
    button_productos = gtk_button_new_with_label("Productos");
    g_signal_connect(button_productos, "clicked", G_CALLBACK(on_productos_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_productos, 0, 0, 1, 1);

    // Botón para el módulo de clientes
    button_clientes = gtk_button_new_with_label("Clientes");
    g_signal_connect(button_clientes, "clicked", G_CALLBACK(on_clientes_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_clientes, 0, 1, 1, 1);

    // Botón para el módulo de facturas
    button_facturas = gtk_button_new_with_label("Facturas");
    g_signal_connect(button_facturas, "clicked", G_CALLBACK(on_facturas_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_facturas, 0, 2, 1, 1);
    
    // Botón para el módulo de ventas
    button_ventas = gtk_button_new_with_label("Ventas");
    g_signal_connect(button_ventas, "clicked", G_CALLBACK(on_ventas_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_ventas, 0, 3, 1, 1);
    
    // Botón para el módulo de control de cajas
    button_control_cajas = gtk_button_new_with_label("Control de Cajas");
    g_signal_connect(button_control_cajas, "clicked", G_CALLBACK(on_control_cajas_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_control_cajas, 1, 0, 1, 1);    

    // Botón para el módulo de trabajadores
    button_trabajadores = gtk_button_new_with_label("Trabajadores");
    g_signal_connect(button_trabajadores, "clicked", G_CALLBACK(on_trabajadores_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_trabajadores, 1, 1, 1, 1);

    // Botón para el módulo de reportes
    button_reportes = gtk_button_new_with_label("Reportes");
    g_signal_connect(button_reportes, "clicked", G_CALLBACK(on_reportes_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_reportes, 1, 2, 1, 1);

    // Mostrar la ventana
    gtk_widget_show_all(window);

    // Iniciar el bucle principal de GTK
    gtk_main();

    return 0;
}

// Función para manejar el clic en el botón "Total Ventas"
void on_total_vendido_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;

    // Crear una nueva ventana para mostrar el reporte
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Total Ventas");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Calcular los totales de ventas
    float total_diario = 0, total_semanal = 0, total_mensual = 0;
    GList *l;
    for (l = facturas; l != NULL; l = l->next) {
        Factura *factura = (Factura *)l->data;
        total_diario += factura->total; // Aquí debes implementar la lógica para calcular los totales diarios, semanales y mensuales.
    }

    // Mostrar los resultados en una etiqueta
    label = gtk_label_new(NULL);
    gchar *text = g_strdup_printf("Total Ventas:\n"
                                  "Diarias: %.2f\n"
                                  "Semanales: %.2f\n"
                                  "Mensuales: %.2f\n",
                                  total_diario, total_semanal, total_mensual);
    gtk_label_set_text(GTK_LABEL(label), text);
    g_free(text);

    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Cantidad de Trabajadores"
void on_cantidad_trabajadores_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;

    // Crear una nueva ventana para mostrar el reporte
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Cantidad de Trabajadores");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 100);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Calcular la cantidad de trabajadores
    int cantidad_trabajadores = g_list_length(trabajadores);

    // Mostrar el resultado en una etiqueta
    label = gtk_label_new(NULL);
    gchar *text = g_strdup_printf("Cantidad de trabajadores: %d", cantidad_trabajadores);
    gtk_label_set_text(GTK_LABEL(label), text);
    g_free(text);

    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Ultimas Facturas"
void on_ultimas_facturas_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *scroll;
    GtkWidget *view;
    GtkTextBuffer *buffer;

    // Crear una nueva ventana para mostrar el reporte
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Ultimas Facturas");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Crear un área de texto con scroll
    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_hexpand(scroll, TRUE);
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_grid_attach(GTK_GRID(grid), scroll, 0, 0, 1, 1);

    view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
    gtk_container_add(GTK_CONTAINER(scroll), view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

    // Mostrar las últimas 10 facturas
    GString *text = g_string_new(NULL);
    GList *l;
    int count = 0;
    for (l = g_list_last(facturas); l != NULL && count < 10; l = l->prev, count++) {
        Factura *factura = (Factura *)l->data;
        g_string_append_printf(text, 
            "Factura N#: %d\n"
            "Fecha: %s\n"
            "Cedula del Cliente: %s\n"
            "Total: %.2f\n\n",
            count + 1,
            factura->fecha,
            factura->cedula_cliente,
            factura->total);
    }

    // Insertar el texto en el buffer
    gtk_text_buffer_set_text(buffer, text->str, -1);

    // Liberar la memoria del string
    g_string_free(text, TRUE);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Productos más Vendidos"
void on_productos_mas_vendidos_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *scroll;
    GtkWidget *view;
    GtkTextBuffer *buffer;

    // Crear una nueva ventana para mostrar el reporte
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Productos mas vendidos");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Crear un área de texto con scroll
    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_hexpand(scroll, TRUE);
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_grid_attach(GTK_GRID(grid), scroll, 0, 0, 1, 1);

    view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
    gtk_container_add(GTK_CONTAINER(scroll), view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

    // Encontrar el producto más vendido
    Producto *producto_mas_vendido = NULL;
    int max_cantidad = 0;
    GList *l;
    for (l = productos; l != NULL; l = l->next) {
        Producto *producto = (Producto *)l->data;
        if (producto->cantidad > max_cantidad) {
            max_cantidad = producto->cantidad;
            producto_mas_vendido = producto;
        }
    }

    // Mostrar el resultado en el área de texto
    if (producto_mas_vendido != NULL) {
        gchar *text = g_strdup_printf("Producto mas vendido:\n"
                                      "Nombre del Producto: %s\n"
                                      "Cantidad Vendida: %d\n",
                                      producto_mas_vendido->nombre, max_cantidad);
        gtk_text_buffer_set_text(buffer, text, -1);
        g_free(text);
    } else {
        gtk_text_buffer_set_text(buffer, "No hay productos vendidos.", -1);
    }

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Clientes con Compras Realizadas"
void on_clientes_compras_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *scroll;
    GtkWidget *view;
    GtkTextBuffer *buffer;

    // Crear una nueva ventana para mostrar el reporte
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Compras Realizadas");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Crear un área de texto con scroll
    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_hexpand(scroll, TRUE);
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_grid_attach(GTK_GRID(grid), scroll, 0, 0, 1, 1);

    view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
    gtk_container_add(GTK_CONTAINER(scroll), view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

    // Calcular la cantidad de clientes con compras
    int cantidad_clientes = 0;
    GList *l;
    for (l = clientes; l != NULL; l = l->next) {
        Cliente *cliente = (Cliente *)l->data;
        // Verificar si el cliente tiene facturas
        GList *f;
        for (f = facturas; f != NULL; f = f->next) {
            Factura *factura = (Factura *)f->data;
            if (strcmp(factura->cedula_cliente, cliente->cedula) == 0) {
                cantidad_clientes++;
                break;
            }
        }
    }

    // Mostrar el resultado en el área de texto
    gchar *text = g_strdup_printf("Clientes con Compras Realizadas: %d\n", cantidad_clientes);
    gtk_text_buffer_set_text(buffer, text, -1);
    g_free(text);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Reportes"
void on_reportes_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button_clientes_compras, *button_productos_mas_vendidos, *button_ultimas_facturas, *button_cantidad_trabajadores, *button_total_vendido;

    // Crear una nueva ventana para el módulo de reportes
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Reportes");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    // Crear un grid para organizar los botones
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Botón "Clientes con Compras Realizadas"
    button_clientes_compras = gtk_button_new_with_label("Compras Realizadas");
    g_signal_connect(button_clientes_compras, "clicked", G_CALLBACK(on_clientes_compras_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_clientes_compras, 0, 0, 1, 1);

    // Botón "Productos más vendidos"
    button_productos_mas_vendidos = gtk_button_new_with_label("Productos mas vendidos");
    g_signal_connect(button_productos_mas_vendidos, "clicked", G_CALLBACK(on_productos_mas_vendidos_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_productos_mas_vendidos, 0, 1, 1, 1);

    // Botón "Últimas Facturas"
    button_ultimas_facturas = gtk_button_new_with_label("Ultimas Facturas");
    g_signal_connect(button_ultimas_facturas, "clicked", G_CALLBACK(on_ultimas_facturas_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_ultimas_facturas, 0, 2, 1, 1);

    // Botón "Cantidad de Trabajadores"
    button_cantidad_trabajadores = gtk_button_new_with_label("Cantidad de Trabajadores");
    g_signal_connect(button_cantidad_trabajadores, "clicked", G_CALLBACK(on_cantidad_trabajadores_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_cantidad_trabajadores, 0, 3, 1, 1);

    // Botón "Total Vendido"
    button_total_vendido = gtk_button_new_with_label("Total Ventas");
    g_signal_connect(button_total_vendido, "clicked", G_CALLBACK(on_total_vendido_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_total_vendido, 0, 4, 1, 1);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón botón "Trabajadores"
void on_trabajadores_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button_crear, *button_modificar, *button_eliminar, *button_mostrar;

    // Crear una nueva ventana para el módulo de trabajadores
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Control de Trabajadores");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    // Crear un grid para organizar los botones
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Botón "Crear Trabajador"
    button_crear = gtk_button_new_with_label("Crear Trabajador");
    g_signal_connect(button_crear, "clicked", G_CALLBACK(on_crear_trabajador_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_crear, 0, 0, 1, 1);

    // Botón "Modificar Trabajador"
    button_modificar = gtk_button_new_with_label("Modificar Trabajador");
    g_signal_connect(button_modificar, "clicked", G_CALLBACK(on_modificar_trabajador_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_modificar, 0, 1, 1, 1);

    // Botón "Eliminar Trabajador"
    button_eliminar = gtk_button_new_with_label("Eliminar Trabajador");
    g_signal_connect(button_eliminar, "clicked", G_CALLBACK(on_eliminar_trabajador_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_eliminar, 0, 2, 1, 1);

    // Botón "Mostrar Trabajadores"
    button_mostrar = gtk_button_new_with_label("Mostrar Trabajadores");
    g_signal_connect(button_mostrar, "clicked", G_CALLBACK(on_mostrar_trabajadores_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_mostrar, 0, 3, 1, 1);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Crear Trabajador"
void on_crear_trabajador_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label_nombre, *label_apellido, *label_cedula, *label_numero, *label_telefono, *label_direccion;
    GtkWidget *entry_nombre, *entry_apellido, *entry_cedula, *entry_numero, *entry_telefono, *entry_direccion;
    GtkWidget *button_guardar;

    // Crear una nueva ventana para "Crear Trabajador"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Crear Trabajador");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para el nombre del trabajador
    label_nombre = gtk_label_new("Nombre del Trabajador:");
    gtk_grid_attach(GTK_GRID(grid), label_nombre, 0, 0, 1, 1);
    entry_nombre = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_nombre, 1, 0, 1, 1);

    // Campo de entrada para el apellido del trabajador
    label_apellido = gtk_label_new("Apellido del Trabajador:");
    gtk_grid_attach(GTK_GRID(grid), label_apellido, 0, 1, 1, 1);
    entry_apellido = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_apellido, 1, 1, 1, 1);

    // Campo de entrada para la cédula del trabajador
    label_cedula = gtk_label_new("Cedula del Trabajador:");
    gtk_grid_attach(GTK_GRID(grid), label_cedula, 0, 2, 1, 1);
    entry_cedula = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_cedula, 1, 2, 1, 1);

    // Campo de entrada para el número de trabajador
    label_numero = gtk_label_new("Numero de Trabajador:");
    gtk_grid_attach(GTK_GRID(grid), label_numero, 0, 3, 1, 1);
    entry_numero = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_numero, 1, 3, 1, 1);

    // Campo de entrada para el teléfono del trabajador
    label_telefono = gtk_label_new("Telefono del Trabajador:");
    gtk_grid_attach(GTK_GRID(grid), label_telefono, 0, 4, 1, 1);
    entry_telefono = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_telefono, 1, 4, 1, 1);

    // Campo de entrada para la dirección del trabajador
    label_direccion = gtk_label_new("Direccion del Trabajador:");
    gtk_grid_attach(GTK_GRID(grid), label_direccion, 0, 5, 1, 1);
    entry_direccion = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_direccion, 1, 5, 1, 1);

    // Botón para guardar el trabajador
    button_guardar = gtk_button_new_with_label("Guardar Trabajador");
    gtk_grid_attach(GTK_GRID(grid), button_guardar, 0, 6, 2, 1);

    // Conectar la señal del botón "Guardar Trabajador"
    g_signal_connect(button_guardar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_nombre = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_nombre"));
        GtkEntry *entry_apellido = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_apellido"));
        GtkEntry *entry_cedula = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_cedula"));
        GtkEntry *entry_numero = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_numero"));
        GtkEntry *entry_telefono = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_telefono"));
        GtkEntry *entry_direccion = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_direccion"));

        const char *nombre = gtk_entry_get_text(entry_nombre);
        const char *apellido = gtk_entry_get_text(entry_apellido);
        const char *cedula = gtk_entry_get_text(entry_cedula);
        const char *numero = gtk_entry_get_text(entry_numero);
        const char *telefono = gtk_entry_get_text(entry_telefono);
        const char *direccion = gtk_entry_get_text(entry_direccion);

        // Validar que los campos no estén vacíos
        if (strlen(nombre) == 0 || strlen(apellido) == 0 || strlen(cedula) == 0 || strlen(numero) == 0 || strlen(telefono) == 0 || strlen(direccion) == 0) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Por favor, complete todos los campos.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Crear un nuevo trabajador
        Trabajador *trabajador = g_new(Trabajador, 1);
        strncpy(trabajador->nombre, nombre, sizeof(trabajador->nombre));
        strncpy(trabajador->apellido, apellido, sizeof(trabajador->apellido));
        strncpy(trabajador->cedula, cedula, sizeof(trabajador->cedula));
        strncpy(trabajador->numero_trabajador, numero, sizeof(trabajador->numero_trabajador));
        strncpy(trabajador->telefono, telefono, sizeof(trabajador->telefono));
        strncpy(trabajador->direccion, direccion, sizeof(trabajador->direccion));

        // Agregar el trabajador a la lista
        trabajadores = g_list_append(trabajadores, trabajador);

        // Mostrar un mensaje de éxito
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Trabajador creado exitosamente.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Cerrar la ventana después de guardar
        gtk_widget_destroy(GTK_WIDGET(data));
    }), window);

    // Asignar los campos de entrada como datos de la ventana
    g_object_set_data(G_OBJECT(window), "entry_nombre", entry_nombre);
    g_object_set_data(G_OBJECT(window), "entry_apellido", entry_apellido);
    g_object_set_data(G_OBJECT(window), "entry_cedula", entry_cedula);
    g_object_set_data(G_OBJECT(window), "entry_numero", entry_numero);
    g_object_set_data(G_OBJECT(window), "entry_telefono", entry_telefono);
    g_object_set_data(G_OBJECT(window), "entry_direccion", entry_direccion);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Modificar Trabajador"
void on_modificar_trabajador_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label_cedula, *label_nombre, *label_apellido, *label_numero, *label_telefono, *label_direccion;
    GtkWidget *entry_cedula, *entry_nombre, *entry_apellido, *entry_numero, *entry_telefono, *entry_direccion;
    GtkWidget *button_buscar, *button_guardar;

    // Crear una nueva ventana para "Modificar Trabajador"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Modificar Trabajador");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para la cédula del trabajador
    label_cedula = gtk_label_new("Cedula del Trabajador:");
    gtk_grid_attach(GTK_GRID(grid), label_cedula, 0, 0, 1, 1);
    entry_cedula = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_cedula, 1, 0, 1, 1);

    // Botón para buscar el trabajador
    button_buscar = gtk_button_new_with_label("Buscar Trabajador");
    gtk_grid_attach(GTK_GRID(grid), button_buscar, 0, 1, 2, 1);

    // Conectar la señal del botón "Buscar Trabajador"
    g_signal_connect(button_buscar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_cedula = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_cedula"));
        const char *cedula = gtk_entry_get_text(entry_cedula);

        // Buscar el trabajador en la lista
        GList *l;
        Trabajador *trabajador_encontrado = NULL;
        for (l = trabajadores; l != NULL; l = l->next) {
            Trabajador *trabajador = (Trabajador *)l->data;
            if (strcmp(trabajador->cedula, cedula) == 0) {
                trabajador_encontrado = trabajador;
                break;
            }
        }

        if (trabajador_encontrado == NULL) {
            // Mostrar un mensaje de error si el trabajador no existe
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Trabajador no encontrado.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Mostrar los datos del trabajador en los campos de entrada
        GtkEntry *entry_nombre = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_nombre"));
        GtkEntry *entry_apellido = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_apellido"));
        GtkEntry *entry_numero = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_numero"));
        GtkEntry *entry_telefono = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_telefono"));
        GtkEntry *entry_direccion = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_direccion"));

        gtk_entry_set_text(entry_nombre, trabajador_encontrado->nombre);
        gtk_entry_set_text(entry_apellido, trabajador_encontrado->apellido);
        gtk_entry_set_text(entry_numero, trabajador_encontrado->numero_trabajador);
        gtk_entry_set_text(entry_telefono, trabajador_encontrado->telefono);
        gtk_entry_set_text(entry_direccion, trabajador_encontrado->direccion);
    }), window);

    // Campo de entrada para el nombre del trabajador
    label_nombre = gtk_label_new("Nombre del Trabajador:");
    gtk_grid_attach(GTK_GRID(grid), label_nombre, 0, 2, 1, 1);
    entry_nombre = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_nombre, 1, 2, 1, 1);

    // Campo de entrada para el apellido del trabajador
    label_apellido = gtk_label_new("Apellido del Trabajador:");
    gtk_grid_attach(GTK_GRID(grid), label_apellido, 0, 3, 1, 1);
    entry_apellido = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_apellido, 1, 3, 1, 1);

    // Campo de entrada para el número de trabajador
    label_numero = gtk_label_new("Numero de Trabajador:");
    gtk_grid_attach(GTK_GRID(grid), label_numero, 0, 4, 1, 1);
    entry_numero = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_numero, 1, 4, 1, 1);

    // Campo de entrada para el teléfono del trabajador
    label_telefono = gtk_label_new("Telefono del Trabajador:");
    gtk_grid_attach(GTK_GRID(grid), label_telefono, 0, 5, 1, 1);
    entry_telefono = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_telefono, 1, 5, 1, 1);

    // Campo de entrada para la dirección del trabajador
    label_direccion = gtk_label_new("Direccion del Trabajador:");
    gtk_grid_attach(GTK_GRID(grid), label_direccion, 0, 6, 1, 1);
    entry_direccion = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_direccion, 1, 6, 1, 1);

    // Botón para guardar los cambios
    button_guardar = gtk_button_new_with_label("Guardar Cambios");
    gtk_grid_attach(GTK_GRID(grid), button_guardar, 0, 7, 2, 1);

    // Conectar la señal del botón "Guardar Cambios"
    g_signal_connect(button_guardar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_cedula = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_cedula"));
        GtkEntry *entry_nombre = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_nombre"));
        GtkEntry *entry_apellido = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_apellido"));
        GtkEntry *entry_numero = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_numero"));
        GtkEntry *entry_telefono = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_telefono"));
        GtkEntry *entry_direccion = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_direccion"));

        const char *cedula = gtk_entry_get_text(entry_cedula);
        const char *nombre = gtk_entry_get_text(entry_nombre);
        const char *apellido = gtk_entry_get_text(entry_apellido);
        const char *numero = gtk_entry_get_text(entry_numero);
        const char *telefono = gtk_entry_get_text(entry_telefono);
        const char *direccion = gtk_entry_get_text(entry_direccion);

        // Buscar el trabajador en la lista
        GList *l;
        Trabajador *trabajador_encontrado = NULL;
        for (l = trabajadores; l != NULL; l = l->next) {
            Trabajador *trabajador = (Trabajador *)l->data;
            if (strcmp(trabajador->cedula, cedula) == 0) {
                trabajador_encontrado = trabajador;
                break;
            }
        }

        if (trabajador_encontrado == NULL) {
            // Mostrar un mensaje de error si el trabajador no existe
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Trabajador no encontrado.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Modificar el trabajador
        strncpy(trabajador_encontrado->nombre, nombre, sizeof(trabajador_encontrado->nombre));
        strncpy(trabajador_encontrado->apellido, apellido, sizeof(trabajador_encontrado->apellido));
        strncpy(trabajador_encontrado->numero_trabajador, numero, sizeof(trabajador_encontrado->numero_trabajador));
        strncpy(trabajador_encontrado->telefono, telefono, sizeof(trabajador_encontrado->telefono));
        strncpy(trabajador_encontrado->direccion, direccion, sizeof(trabajador_encontrado->direccion));

        // Mostrar un mensaje de éxito
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Trabajador modificado exitosamente.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Cerrar la ventana después de guardar
        gtk_widget_destroy(GTK_WIDGET(data));
    }), window);

    // Asignar los campos de entrada como datos de la ventana
    g_object_set_data(G_OBJECT(window), "entry_cedula", entry_cedula);
    g_object_set_data(G_OBJECT(window), "entry_nombre", entry_nombre);
    g_object_set_data(G_OBJECT(window), "entry_apellido", entry_apellido);
    g_object_set_data(G_OBJECT(window), "entry_numero", entry_numero);
    g_object_set_data(G_OBJECT(window), "entry_telefono", entry_telefono);
    g_object_set_data(G_OBJECT(window), "entry_direccion", entry_direccion);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Eliminar Trabajador"
void on_eliminar_trabajador_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label_cedula;
    GtkWidget *entry_cedula;
    GtkWidget *button_eliminar;

    // Crear una nueva ventana para "Eliminar Trabajador"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Eliminar Trabajador");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 100);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para la cédula del trabajador
    label_cedula = gtk_label_new("Cedula del Trabajador:");
    gtk_grid_attach(GTK_GRID(grid), label_cedula, 0, 0, 1, 1);
    entry_cedula = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_cedula, 1, 0, 1, 1);

    // Botón para eliminar el trabajador
    button_eliminar = gtk_button_new_with_label("Eliminar Trabajador");
    gtk_grid_attach(GTK_GRID(grid), button_eliminar, 0, 1, 2, 1);

    // Conectar la señal del botón "Eliminar Trabajador"
    g_signal_connect(button_eliminar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_cedula = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_cedula"));
        const char *cedula = gtk_entry_get_text(entry_cedula);

        // Buscar el trabajador en la lista
        GList *l;
        Trabajador *trabajador_encontrado = NULL;
        for (l = trabajadores; l != NULL; l = l->next) {
            Trabajador *trabajador = (Trabajador *)l->data;
            if (strcmp(trabajador->cedula, cedula) == 0) {
                trabajador_encontrado = trabajador;
                break;
            }
        }

        if (trabajador_encontrado == NULL) {
            // Mostrar un mensaje de error si el trabajador no existe
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Trabajador no encontrado.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Eliminar el trabajador de la lista
        trabajadores = g_list_remove(trabajadores, trabajador_encontrado);
        g_free(trabajador_encontrado);

        // Mostrar un mensaje de éxito
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Trabajador eliminado exitosamente.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Cerrar la ventana después de eliminar
        gtk_widget_destroy(GTK_WIDGET(data));
    }), window);

    // Asignar el campo de entrada como dato de la ventana
    g_object_set_data(G_OBJECT(window), "entry_cedula", entry_cedula);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Mostrar Trabajadores"
void on_mostrar_trabajadores_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *scroll;
    GtkWidget *view;
    GtkTextBuffer *buffer;

    // Crear una nueva ventana para "Mostrar Trabajadores"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mostrar Trabajadores");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Crear un área de texto con scroll
    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_hexpand(scroll, TRUE);
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_grid_attach(GTK_GRID(grid), scroll, 0, 0, 1, 1);

    view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
    gtk_container_add(GTK_CONTAINER(scroll), view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

    // Verificar si hay trabajadores en la lista
    if (trabajadores == NULL) {
        gtk_text_buffer_set_text(buffer, "No hay trabajadores registrados.", -1);
    } else {
        // Crear un string para almacenar los trabajadores
        GString *text = g_string_new(NULL);

        // Recorrer la lista de trabajadores
        GList *l;
        for (l = trabajadores; l != NULL; l = l->next) {
            Trabajador *trabajador = (Trabajador *)l->data;

            // Agregar la información del trabajador al string
            g_string_append_printf(text, 
                "Nombre: %s\n"
                "Apellido: %s\n"
                "Cedula: %s\n"
                "Numero de Trabajador: %s\n"
                "Telefono: %s\n"
                "Direccion: %s\n\n",
                trabajador->nombre,
                trabajador->apellido,
                trabajador->cedula,
                trabajador->numero_trabajador,
                trabajador->telefono,
                trabajador->direccion);
        }

        // Insertar el texto en el buffer
        gtk_text_buffer_set_text(buffer, text->str, -1);

        // Liberar la memoria del string
        g_string_free(text, TRUE);
    }

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Control de Cajas"
void on_control_cajas_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button_crear, *button_modificar, *button_eliminar, *button_mostrar;

    // Crear una nueva ventana para el módulo de control de cajas
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Control de Cajas");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    // Crear un grid para organizar los botones
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Botón "Crear Caja"
    button_crear = gtk_button_new_with_label("Crear Caja");
    g_signal_connect(button_crear, "clicked", G_CALLBACK(on_crear_caja_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_crear, 0, 0, 1, 1);

    // Botón "Modificar Caja"
    button_modificar = gtk_button_new_with_label("Modificar Caja");
    g_signal_connect(button_modificar, "clicked", G_CALLBACK(on_modificar_caja_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_modificar, 0, 1, 1, 1);

    // Botón "Eliminar Caja"
    button_eliminar = gtk_button_new_with_label("Eliminar Caja");
    g_signal_connect(button_eliminar, "clicked", G_CALLBACK(on_eliminar_caja_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_eliminar, 0, 2, 1, 1);

    // Botón "Mostrar Cajas"
    button_mostrar = gtk_button_new_with_label("Mostrar Cajas");
    g_signal_connect(button_mostrar, "clicked", G_CALLBACK(on_mostrar_cajas_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_mostrar, 0, 3, 1, 1);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Crear Caja"
void on_crear_caja_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label_numero, *label_responsable;
    GtkWidget *entry_numero, *entry_responsable;
    GtkWidget *button_guardar;

    // Crear una nueva ventana para "Crear Caja"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Crear Caja");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 150);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para el número de caja
    label_numero = gtk_label_new("Numero de caja:");
    gtk_grid_attach(GTK_GRID(grid), label_numero, 0, 0, 1, 1);
    entry_numero = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_numero, 1, 0, 1, 1);

    // Campo de entrada para el nombre del responsable
    label_responsable = gtk_label_new("Nombre del responsable:");
    gtk_grid_attach(GTK_GRID(grid), label_responsable, 0, 1, 1, 1);
    entry_responsable = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_responsable, 1, 1, 1, 1);

    // Botón para guardar la caja
    button_guardar = gtk_button_new_with_label("Guardar Caja");
    gtk_grid_attach(GTK_GRID(grid), button_guardar, 0, 2, 2, 1);

    // Conectar la señal del botón "Guardar Caja"
    g_signal_connect(button_guardar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_numero = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_numero"));
        GtkEntry *entry_responsable = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_responsable"));

        const char *numero_str = gtk_entry_get_text(entry_numero);
        const char *responsable = gtk_entry_get_text(entry_responsable);

        // Validar que los campos no estén vacíos
        if (strlen(numero_str) == 0 || strlen(responsable) == 0) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Por favor, complete todos los campos.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Convertir el número de caja a un entero
        int numero_caja = atoi(numero_str);

        // Crear una nueva caja
        Caja *caja = g_new(Caja, 1);
        caja->numero_caja = numero_caja;
        strncpy(caja->responsable, responsable, sizeof(caja->responsable));
        caja->total_bs = 0;
        caja->total_pesos = 0;
        caja->total_dolares = 0;
        caja->total_euros = 0;

        // Agregar la caja a la lista
        cajas = g_list_append(cajas, caja);

        // Mostrar un mensaje de éxito
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Caja creada exitosamente.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Cerrar la ventana después de guardar
        gtk_widget_destroy(GTK_WIDGET(data));
    }), window);

    // Asignar los campos de entrada como datos de la ventana
    g_object_set_data(G_OBJECT(window), "entry_numero", entry_numero);
    g_object_set_data(G_OBJECT(window), "entry_responsable", entry_responsable);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Modiifcar Caja"
void on_modificar_caja_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label_numero, *label_responsable, *label_bs, *label_pesos, *label_dolares, *label_euros;
    GtkWidget *entry_numero, *entry_responsable, *entry_bs, *entry_pesos, *entry_dolares, *entry_euros;
    GtkWidget *button_buscar, *button_guardar;

    // Crear una nueva ventana para "Modificar Caja"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Modificar Caja");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para el número de caja
    label_numero = gtk_label_new("Numero de caja a modificar:");
    gtk_grid_attach(GTK_GRID(grid), label_numero, 0, 0, 1, 1);
    entry_numero = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_numero, 1, 0, 1, 1);

    // Botón para buscar la caja
    button_buscar = gtk_button_new_with_label("Buscar Caja");
    gtk_grid_attach(GTK_GRID(grid), button_buscar, 0, 1, 2, 1);

    // Conectar la señal del botón "Buscar Caja"
    g_signal_connect(button_buscar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_numero = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_numero"));
        const char *numero_str = gtk_entry_get_text(entry_numero);
        int numero_caja = atoi(numero_str);

        // Buscar la caja en la lista
        GList *l;
        Caja *caja_encontrada = NULL;
        for (l = cajas; l != NULL; l = l->next) {
            Caja *caja = (Caja *)l->data;
            if (caja->numero_caja == numero_caja) {
                caja_encontrada = caja;
                break;
            }
        }

        if (caja_encontrada == NULL) {
            // Mostrar un mensaje de error si la caja no existe
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Caja no encontrada.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Mostrar los datos de la caja en los campos de entrada
        GtkEntry *entry_responsable = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_responsable"));
        GtkEntry *entry_bs = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_bs"));
        GtkEntry *entry_pesos = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_pesos"));
        GtkEntry *entry_dolares = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_dolares"));
        GtkEntry *entry_euros = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_euros"));

        gtk_entry_set_text(entry_responsable, caja_encontrada->responsable);
        gtk_entry_set_text(entry_bs, g_strdup_printf("%.2f", caja_encontrada->total_bs));
        gtk_entry_set_text(entry_pesos, g_strdup_printf("%.2f", caja_encontrada->total_pesos));
        gtk_entry_set_text(entry_dolares, g_strdup_printf("%.2f", caja_encontrada->total_dolares));
        gtk_entry_set_text(entry_euros, g_strdup_printf("%.2f", caja_encontrada->total_euros));
    }), window);

    // Campo de entrada para el nombre del responsable
    label_responsable = gtk_label_new("Nombre del responsable:");
    gtk_grid_attach(GTK_GRID(grid), label_responsable, 0, 2, 1, 1);
    entry_responsable = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_responsable, 1, 2, 1, 1);

    // Campo de entrada para el total facturado en Bs
    label_bs = gtk_label_new("Total Facturado en Bs:");
    gtk_grid_attach(GTK_GRID(grid), label_bs, 0, 3, 1, 1);
    entry_bs = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_bs, 1, 3, 1, 1);

    // Campo de entrada para el total facturado en Pesos
    label_pesos = gtk_label_new("Total Facturado en Pesos:");
    gtk_grid_attach(GTK_GRID(grid), label_pesos, 0, 4, 1, 1);
    entry_pesos = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_pesos, 1, 4, 1, 1);

    // Campo de entrada para el total facturado en Dólares
    label_dolares = gtk_label_new("Total Facturado en Dolares:");
    gtk_grid_attach(GTK_GRID(grid), label_dolares, 0, 5, 1, 1);
    entry_dolares = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_dolares, 1, 5, 1, 1);

    // Campo de entrada para el total facturado en Euros
    label_euros = gtk_label_new("Total Facturado en Euros:");
    gtk_grid_attach(GTK_GRID(grid), label_euros, 0, 6, 1, 1);
    entry_euros = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_euros, 1, 6, 1, 1);

    // Botón para guardar los cambios
    button_guardar = gtk_button_new_with_label("Guardar Cambios");
    gtk_grid_attach(GTK_GRID(grid), button_guardar, 0, 7, 2, 1);

    // Conectar la señal del botón "Guardar Cambios"
    g_signal_connect(button_guardar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_numero = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_numero"));
        GtkEntry *entry_responsable = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_responsable"));
        GtkEntry *entry_bs = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_bs"));
        GtkEntry *entry_pesos = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_pesos"));
        GtkEntry *entry_dolares = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_dolares"));
        GtkEntry *entry_euros = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_euros"));

        const char *numero_str = gtk_entry_get_text(entry_numero);
        const char *responsable = gtk_entry_get_text(entry_responsable);
        const char *bs_str = gtk_entry_get_text(entry_bs);
        const char *pesos_str = gtk_entry_get_text(entry_pesos);
        const char *dolares_str = gtk_entry_get_text(entry_dolares);
        const char *euros_str = gtk_entry_get_text(entry_euros);

        // Convertir los valores a números
        int numero_caja = atoi(numero_str);
        float total_bs = atof(bs_str);
        float total_pesos = atof(pesos_str);
        float total_dolares = atof(dolares_str);
        float total_euros = atof(euros_str);

        // Buscar la caja en la lista
        GList *l;
        Caja *caja_encontrada = NULL;
        for (l = cajas; l != NULL; l = l->next) {
            Caja *caja = (Caja *)l->data;
            if (caja->numero_caja == numero_caja) {
                caja_encontrada = caja;
                break;
            }
        }

        if (caja_encontrada == NULL) {
            // Mostrar un mensaje de error si la caja no existe
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Caja no encontrada.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Modificar la caja
        strncpy(caja_encontrada->responsable, responsable, sizeof(caja_encontrada->responsable));
        caja_encontrada->total_bs = total_bs;
        caja_encontrada->total_pesos = total_pesos;
        caja_encontrada->total_dolares = total_dolares;
        caja_encontrada->total_euros = total_euros;

        // Mostrar un mensaje de éxito
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Caja modificada exitosamente.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Cerrar la ventana después de guardar
        gtk_widget_destroy(GTK_WIDGET(data));
    }), window);

    // Asignar los campos de entrada como datos de la ventana
    g_object_set_data(G_OBJECT(window), "entry_numero", entry_numero);
    g_object_set_data(G_OBJECT(window), "entry_responsable", entry_responsable);
    g_object_set_data(G_OBJECT(window), "entry_bs", entry_bs);
    g_object_set_data(G_OBJECT(window), "entry_pesos", entry_pesos);
    g_object_set_data(G_OBJECT(window), "entry_dolares", entry_dolares);
    g_object_set_data(G_OBJECT(window), "entry_euros", entry_euros);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Eliminar Caja"
void on_eliminar_caja_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label_numero;
    GtkWidget *entry_numero;
    GtkWidget *button_eliminar;

    // Crear una nueva ventana para "Eliminar Caja"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Eliminar Caja");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 100);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para el número de caja
    label_numero = gtk_label_new("Numero de caja a eliminar:");
    gtk_grid_attach(GTK_GRID(grid), label_numero, 0, 0, 1, 1);
    entry_numero = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_numero, 1, 0, 1, 1);

    // Botón para eliminar la caja
    button_eliminar = gtk_button_new_with_label("Eliminar Caja");
    gtk_grid_attach(GTK_GRID(grid), button_eliminar, 0, 1, 2, 1);

    // Conectar la señal del botón "Eliminar Caja"
    g_signal_connect(button_eliminar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_numero = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_numero"));
        const char *numero_str = gtk_entry_get_text(entry_numero);
        int numero_caja = atoi(numero_str);

        // Buscar la caja en la lista
        GList *l;
        Caja *caja_encontrada = NULL;
        for (l = cajas; l != NULL; l = l->next) {
            Caja *caja = (Caja *)l->data;
            if (caja->numero_caja == numero_caja) {
                caja_encontrada = caja;
                break;
            }
        }

        if (caja_encontrada == NULL) {
            // Mostrar un mensaje de error si la caja no existe
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Caja no encontrada.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Eliminar la caja de la lista
        cajas = g_list_remove(cajas, caja_encontrada);
        g_free(caja_encontrada);

        // Mostrar un mensaje de éxito
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Caja eliminada exitosamente.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Cerrar la ventana después de eliminar
        gtk_widget_destroy(GTK_WIDGET(data));
    }), window);

    // Asignar el campo de entrada como dato de la ventana
    g_object_set_data(G_OBJECT(window), "entry_numero", entry_numero);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Mostrar Cajas"
void on_mostrar_cajas_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *scroll;
    GtkWidget *view;
    GtkTextBuffer *buffer;

    // Crear una nueva ventana para "Mostrar Cajas"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mostrar Cajas");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Crear un área de texto con scroll
    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_hexpand(scroll, TRUE);
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_grid_attach(GTK_GRID(grid), scroll, 0, 0, 1, 1);

    view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
    gtk_container_add(GTK_CONTAINER(scroll), view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

    // Verificar si hay cajas en la lista
    if (cajas == NULL) {
        gtk_text_buffer_set_text(buffer, "No hay cajas registradas.", -1);
    } else {
        // Crear un string para almacenar las cajas
        GString *text = g_string_new(NULL);

        // Recorrer la lista de cajas
        GList *l;
        for (l = cajas; l != NULL; l = l->next) {
            Caja *caja = (Caja *)l->data;

            // Agregar la información de la caja al string
            g_string_append_printf(text, 
                "Numero de caja: %d\n"
                "Responsable: %s\n"
                "Total Facturado en Bs: %.2f\n"
                "Total Facturado en Pesos: %.2f\n"
                "Total Facturado en Dolares: %.2f\n"
                "Total Facturado en Euros: %.2f\n\n",
                caja->numero_caja,
                caja->responsable,
                caja->total_bs,
                caja->total_pesos,
                caja->total_dolares,
                caja->total_euros);
        }

        // Insertar el texto en el buffer
        gtk_text_buffer_set_text(buffer, text->str, -1);

        // Liberar la memoria del string
        g_string_free(text, TRUE);
    }

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Ventas"
void on_ventas_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button_diarias, *button_semanales, *button_mensuales;

    // Crear una nueva ventana para el módulo de ventas
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Modulo de Ventas");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    // Crear un grid para organizar los botones
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Botón "Mostrar Ventas Diarias"
    button_diarias = gtk_button_new_with_label("Mostrar Ventas Diarias");
    g_signal_connect(button_diarias, "clicked", G_CALLBACK(on_mostrar_ventas_diarias_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_diarias, 0, 0, 1, 1);

    // Botón "Mostrar Ventas Semanales"
    button_semanales = gtk_button_new_with_label("Mostrar Ventas Semanales");
    g_signal_connect(button_semanales, "clicked", G_CALLBACK(on_mostrar_ventas_semanales_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_semanales, 0, 1, 1, 1);

    // Botón "Mostrar Ventas Mensuales"
    button_mensuales = gtk_button_new_with_label("Mostrar Ventas Mensuales");
    g_signal_connect(button_mensuales, "clicked", G_CALLBACK(on_mostrar_ventas_mensuales_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_mensuales, 0, 2, 1, 1);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Productos"
void on_productos_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button_crear, *button_modificar, *button_eliminar, *button_mostrar;

    // Crear una nueva ventana para el módulo de productos
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Modulo de Productos");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    // Crear un grid para organizar los botones
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Botón "Crear Producto"
    button_crear = gtk_button_new_with_label("Crear Producto");
    g_signal_connect(button_crear, "clicked", G_CALLBACK(on_crear_producto_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_crear, 0, 0, 1, 1);

    // Botón "Modificar Producto"
    button_modificar = gtk_button_new_with_label("Modificar Producto");
    g_signal_connect(button_modificar, "clicked", G_CALLBACK(on_modificar_producto_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_modificar, 0, 1, 1, 1);

    // Botón "Eliminar Producto"
    button_eliminar = gtk_button_new_with_label("Eliminar Producto");
    g_signal_connect(button_eliminar, "clicked", G_CALLBACK(on_eliminar_producto_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_eliminar, 0, 2, 1, 1);

    // Botón "Mostrar Productos"
    button_mostrar = gtk_button_new_with_label("Mostrar Productos");
    g_signal_connect(button_mostrar, "clicked", G_CALLBACK(on_mostrar_productos_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_mostrar, 0, 3, 1, 1);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Crear Producto"
void on_crear_producto_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *entry_codigo, *entry_nombre, *entry_cantidad, *entry_precio_bs, *entry_precio_pesos, *entry_precio_dolares, *entry_precio_euros;
    GtkWidget *button_guardar;

    // Crear una nueva ventana para "Crear Producto"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Crear Producto");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para el código del producto
    label = gtk_label_new("Codigo del Producto:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    entry_codigo = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_codigo, 1, 0, 1, 1);

    // Campo de entrada para el nombre del producto
    label = gtk_label_new("Nombre del Producto:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
    entry_nombre = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_nombre, 1, 1, 1, 1);

    // Campo de entrada para la cantidad del producto
    label = gtk_label_new("Cantidad Disponible:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
    entry_cantidad = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_cantidad, 1, 2, 1, 1);

    // Campo de entrada para el precio en Bs
    label = gtk_label_new("Precio en Bs:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);
    entry_precio_bs = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_precio_bs, 1, 3, 1, 1);

    // Campo de entrada para el precio en Pesos
    label = gtk_label_new("Precio en Pesos:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 4, 1, 1);
    entry_precio_pesos = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_precio_pesos, 1, 4, 1, 1);

    // Campo de entrada para el precio en Dólares
    label = gtk_label_new("Precio en Dolares:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 5, 1, 1);
    entry_precio_dolares = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_precio_dolares, 1, 5, 1, 1);

    // Campo de entrada para el precio en Euros
    label = gtk_label_new("Precio en Euros:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 6, 1, 1);
    entry_precio_euros = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_precio_euros, 1, 6, 1, 1);

    // Botón para guardar el producto
    button_guardar = gtk_button_new_with_label("Guardar Producto");
    gtk_grid_attach(GTK_GRID(grid), button_guardar, 0, 7, 2, 1);

    // Conectar la señal del botón "Guardar Producto"
    g_signal_connect(button_guardar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_codigo = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_codigo"));
        GtkEntry *entry_nombre = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_nombre"));
        GtkEntry *entry_cantidad = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_cantidad"));
        GtkEntry *entry_precio_bs = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_precio_bs"));
        GtkEntry *entry_precio_pesos = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_precio_pesos"));
        GtkEntry *entry_precio_dolares = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_precio_dolares"));
        GtkEntry *entry_precio_euros = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_precio_euros"));

        // Obtener los valores de los campos de entrada
        const char *codigo_str = gtk_entry_get_text(entry_codigo);
        const char *nombre = gtk_entry_get_text(entry_nombre);
        const char *cantidad_str = gtk_entry_get_text(entry_cantidad);
        const char *precio_bs_str = gtk_entry_get_text(entry_precio_bs);
        const char *precio_pesos_str = gtk_entry_get_text(entry_precio_pesos);
        const char *precio_dolares_str = gtk_entry_get_text(entry_precio_dolares);
        const char *precio_euros_str = gtk_entry_get_text(entry_precio_euros);

        // Convertir los valores a números
        int codigo = atoi(codigo_str);
        int cantidad = atoi(cantidad_str);
        float precio_bs = atof(precio_bs_str);
        float precio_pesos = atof(precio_pesos_str);
        float precio_dolares = atof(precio_dolares_str);
        float precio_euros = atof(precio_euros_str);

        // Crear un nuevo producto
        Producto *producto = g_new(Producto, 1);
        producto->codigo = codigo;
        strncpy(producto->nombre, nombre, sizeof(producto->nombre));
        producto->cantidad = cantidad;
        producto->precio_bs = precio_bs;
        producto->precio_pesos = precio_pesos;
        producto->precio_dolares = precio_dolares;
        producto->precio_euros = precio_euros;

        // Agregar el producto a la lista
        productos = g_list_append(productos, producto);

        // Mostrar un mensaje de éxito
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Producto creado exitosamente");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Cerrar la ventana después de guardar
        gtk_widget_destroy(GTK_WIDGET(data));
    }), window);

    // Asignar los campos de entrada como datos de la ventana
    g_object_set_data(G_OBJECT(window), "entry_codigo", entry_codigo);
    g_object_set_data(G_OBJECT(window), "entry_nombre", entry_nombre);
    g_object_set_data(G_OBJECT(window), "entry_cantidad", entry_cantidad);
    g_object_set_data(G_OBJECT(window), "entry_precio_bs", entry_precio_bs);
    g_object_set_data(G_OBJECT(window), "entry_precio_pesos", entry_precio_pesos);
    g_object_set_data(G_OBJECT(window), "entry_precio_dolares", entry_precio_dolares);
    g_object_set_data(G_OBJECT(window), "entry_precio_euros", entry_precio_euros);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Mostrar Ventas Diarias"
void on_mostrar_ventas_diarias_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *entry_fecha;
    GtkWidget *button_buscar;

    // Crear una nueva ventana para ingresar la fecha
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mostrar Ventas Diarias");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 100);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para la fecha
    label = gtk_label_new("Ingrese la fecha (AAAA/MM/DD):");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    entry_fecha = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_fecha, 1, 0, 1, 1);

    // Botón para buscar las ventas
    button_buscar = gtk_button_new_with_label("Buscar Ventas");
    gtk_grid_attach(GTK_GRID(grid), button_buscar, 0, 1, 2, 1);

    // Conectar la señal del botón "Buscar Ventas"
    g_signal_connect(button_buscar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_fecha = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_fecha"));
        const char *fecha = gtk_entry_get_text(entry_fecha);

        // Verificar si la fecha es válida (puedes agregar más validaciones aquí)
        if (strlen(fecha) == 0) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Por favor, ingrese una fecha valida.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Crear una ventana para mostrar las ventas
        GtkWidget *window_ventas;
        GtkWidget *grid_ventas;
        GtkWidget *scroll;
        GtkWidget *view;
        GtkTextBuffer *buffer;

        window_ventas = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window_ventas), "Ventas del Dia");
        gtk_window_set_default_size(GTK_WINDOW(window_ventas), 500, 400);

        grid_ventas = gtk_grid_new();
        gtk_container_add(GTK_CONTAINER(window_ventas), grid_ventas);

        // Crear un área de texto con scroll
        scroll = gtk_scrolled_window_new(NULL, NULL);
        gtk_widget_set_hexpand(scroll, TRUE);
        gtk_widget_set_vexpand(scroll, TRUE);
        gtk_grid_attach(GTK_GRID(grid_ventas), scroll, 0, 0, 1, 1);

        view = gtk_text_view_new();
        gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
        gtk_container_add(GTK_CONTAINER(scroll), view);

        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

        // Buscar las ventas en la lista global `facturas`
        GString *text = g_string_new(NULL);
        GList *l;
        int ventas_encontradas = 0;

        for (l = facturas; l != NULL; l = l->next) {
            Factura *factura = (Factura *)l->data;

            // Comparar la fecha de la factura con la fecha ingresada
            if (strcmp(factura->fecha, fecha) == 0) {
                ventas_encontradas++;

                // Buscar el cliente por cédula
                Cliente *cliente_encontrado = NULL;
                GList *c;
                for (c = clientes; c != NULL; c = c->next) {
                    Cliente *cliente = (Cliente *)c->data;
                    if (strcmp(cliente->cedula, factura->cedula_cliente) == 0) {
                        cliente_encontrado = cliente;
                        break;
                    }
                }

                // Obtener el nombre y apellido del cliente si se encontró
                const char *nombre_cliente = cliente_encontrado ? cliente_encontrado->nombre : "Desconocido";
                const char *apellido_cliente = cliente_encontrado ? cliente_encontrado->apellido : "Desconocido";

                // Agregar la información de la factura al string
                g_string_append_printf(text, 
                    "Factura N#: %d\n"
                    "Fecha: %s\n"
                    "Cliente: %s %s\n"
                    "Cedula: %s\n"
                    "Subtotal: %.2f\n"
                    "IVA: %.2f\n"
                    "Total: %.2f\n\n",
                    ventas_encontradas,
                    factura->fecha,
                    nombre_cliente, apellido_cliente,
                    factura->cedula_cliente,
                    factura->subtotal,
                    factura->iva,
                    factura->total);
            }
        }

        // Mostrar un mensaje si no se encontraron ventas
        if (ventas_encontradas == 0) {
            g_string_append(text, "No se encontraron ventas para la fecha ingresada.");
        }

        // Insertar el texto en el buffer
        gtk_text_buffer_set_text(buffer, text->str, -1);

        // Liberar la memoria del string
        g_string_free(text, TRUE);

        // Mostrar la ventana
        gtk_widget_show_all(window_ventas);
    }), window);

    // Asignar el campo de entrada como dato de la ventana
    g_object_set_data(G_OBJECT(window), "entry_fecha", entry_fecha);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}


////////////////////////////////////////////////////////////////////////////////
// Función para manejar el clic en el botón "Mostrar Ventas Semanales"
void on_mostrar_ventas_semanales_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label_mes, *label_semana;
    GtkWidget *entry_mes, *entry_semana;
    GtkWidget *button_buscar;

    // Crear una nueva ventana para ingresar el mes y la semana
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mostrar Ventas Semanales");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 150);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para el mes
    label_mes = gtk_label_new("Ingrese el mes (mm):");
    gtk_grid_attach(GTK_GRID(grid), label_mes, 0, 0, 1, 1);
    entry_mes = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_mes, 1, 0, 1, 1);

    // Campo de entrada para la semana
    label_semana = gtk_label_new("Ingrese la semana (01-05):");
    gtk_grid_attach(GTK_GRID(grid), label_semana, 0, 1, 1, 1);
    entry_semana = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_semana, 1, 1, 1, 1);

    // Botón para buscar las ventas
    button_buscar = gtk_button_new_with_label("Buscar Ventas");
    gtk_grid_attach(GTK_GRID(grid), button_buscar, 0, 2, 2, 1);

    // Conectar la señal del botón "Buscar Ventas"
    g_signal_connect(button_buscar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_mes = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_mes"));
        GtkEntry *entry_semana = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_semana"));

        const char *mes = gtk_entry_get_text(entry_mes);
        const char *semana_str = gtk_entry_get_text(entry_semana);

        // Validar que los campos no estén vacíos
        if (strlen(mes) == 0 || strlen(semana_str) == 0) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Por favor, ingrese el mes y la semana.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Convertir la semana a un número entero
        int semana = atoi(semana_str);

        // Validar que la semana esté en el rango 1-5
        if (semana < 1 || semana > 5) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "La semana debe estar entre 01 y 05.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Crear una ventana para mostrar las ventas
        GtkWidget *window_ventas;
        GtkWidget *grid_ventas;
        GtkWidget *scroll;
        GtkWidget *view;
        GtkTextBuffer *buffer;

        window_ventas = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window_ventas), "Ventas Semanales");
        gtk_window_set_default_size(GTK_WINDOW(window_ventas), 500, 400);

        grid_ventas = gtk_grid_new();
        gtk_container_add(GTK_CONTAINER(window_ventas), grid_ventas);

        // Crear un área de texto con scroll
        scroll = gtk_scrolled_window_new(NULL, NULL);
        gtk_widget_set_hexpand(scroll, TRUE);
        gtk_widget_set_vexpand(scroll, TRUE);
        gtk_grid_attach(GTK_GRID(grid_ventas), scroll, 0, 0, 1, 1);

        view = gtk_text_view_new();
        gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
        gtk_container_add(GTK_CONTAINER(scroll), view);

        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

        // Buscar las ventas en la lista global `facturas`
        GString *text = g_string_new(NULL);
        GList *l;
        int ventas_encontradas = 0;

        for (l = facturas; l != NULL; l = l->next) {
            Factura *factura = (Factura *)l->data;

            // Extraer el mes de la fecha de la factura (formato dd/mm/aaaa)
            char factura_mes[3];
            strncpy(factura_mes, factura->fecha + 3, 2); // Extraer los dos dígitos del mes
            factura_mes[2] = '\0';

            // Comparar el mes de la factura con el mes ingresado
            if (strcmp(factura_mes, mes) == 0) {
                // Calcular la semana del mes para la fecha de la factura
                int dia = atoi(factura->fecha); // Extraer el día de la fecha
                int semana_factura = (dia - 1) / 7 + 1; // Calcular la semana (1-5)

                // Comparar la semana de la factura con la semana ingresada
                if (semana_factura == semana) {
                    ventas_encontradas++;

                    // Buscar el cliente por cédula
                    Cliente *cliente_encontrado = NULL;
                    GList *c;
                    for (c = clientes; c != NULL; c = c->next) {
                        Cliente *cliente = (Cliente *)c->data;
                        if (strcmp(cliente->cedula, factura->cedula_cliente) == 0) {
                            cliente_encontrado = cliente;
                            break;
                        }
                    }

                    // Obtener el nombre y apellido del cliente si se encontró
                    const char *nombre_cliente = cliente_encontrado ? cliente_encontrado->nombre : "Desconocido";
                    const char *apellido_cliente = cliente_encontrado ? cliente_encontrado->apellido : "Desconocido";

                    // Agregar la información de la factura al string
                    g_string_append_printf(text, 
                        "Factura N#: %d\n"
                        "Fecha: %s\n"
                        "Cliente: %s %s\n"
                        "Cedula: %s\n"
                        "Subtotal: %.2f\n"
                        "IVA: %.2f\n"
                        "Total: %.2f\n\n",
                        ventas_encontradas,
                        factura->fecha,
                        nombre_cliente, apellido_cliente,
                        factura->cedula_cliente,
                        factura->subtotal,
                        factura->iva,
                        factura->total);
                }
            }
        }

        // Mostrar un mensaje si no se encontraron ventas
        if (ventas_encontradas == 0) {
            g_string_append(text, "No se encontraron ventas para el mes y semana ingresados.");
        }

        // Insertar el texto en el buffer
        gtk_text_buffer_set_text(buffer, text->str, -1);

        // Liberar la memoria del string
        g_string_free(text, TRUE);

        // Mostrar la ventana
        gtk_widget_show_all(window_ventas);
    }), window);

    // Asignar los campos de entrada como datos de la ventana
    g_object_set_data(G_OBJECT(window), "entry_mes", entry_mes);
    g_object_set_data(G_OBJECT(window), "entry_semana", entry_semana);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Mostrar Ventas Mensuales"
void on_mostrar_ventas_mensuales_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label_mes;
    GtkWidget *entry_mes;
    GtkWidget *button_buscar;

    // Crear una nueva ventana para ingresar el mes
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mostrar Ventas Mensuales");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 100);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para el mes
    label_mes = gtk_label_new("Ingrese el mes (mm):");
    gtk_grid_attach(GTK_GRID(grid), label_mes, 0, 0, 1, 1);
    entry_mes = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_mes, 1, 0, 1, 1);

    // Botón para buscar las ventas
    button_buscar = gtk_button_new_with_label("Buscar Ventas");
    gtk_grid_attach(GTK_GRID(grid), button_buscar, 0, 1, 2, 1);

    // Conectar la señal del botón "Buscar Ventas"
    g_signal_connect(button_buscar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_mes = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_mes"));
        const char *mes = gtk_entry_get_text(entry_mes);

        // Validar que el campo no esté vacío
        if (strlen(mes) == 0) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Por favor, ingrese un mes válido.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Crear una ventana para mostrar las ventas
        GtkWidget *window_ventas;
        GtkWidget *grid_ventas;
        GtkWidget *scroll;
        GtkWidget *view;
        GtkTextBuffer *buffer;

        window_ventas = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window_ventas), "Ventas Mensuales");
        gtk_window_set_default_size(GTK_WINDOW(window_ventas), 500, 400);

        grid_ventas = gtk_grid_new();
        gtk_container_add(GTK_CONTAINER(window_ventas), grid_ventas);

        // Crear un área de texto con scroll
        scroll = gtk_scrolled_window_new(NULL, NULL);
        gtk_widget_set_hexpand(scroll, TRUE);
        gtk_widget_set_vexpand(scroll, TRUE);
        gtk_grid_attach(GTK_GRID(grid_ventas), scroll, 0, 0, 1, 1);

        view = gtk_text_view_new();
        gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
        gtk_container_add(GTK_CONTAINER(scroll), view);

        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

        // Buscar las ventas en la lista global `facturas`
        GString *text = g_string_new(NULL);
        GList *l;
        int ventas_encontradas = 0;

        for (l = facturas; l != NULL; l = l->next) {
            Factura *factura = (Factura *)l->data;

            // Extraer el mes de la fecha de la factura (formato dd/mm/aaaa)
            char factura_mes[3];
            strncpy(factura_mes, factura->fecha + 3, 2); // Extraer los dos dígitos del mes
            factura_mes[2] = '\0';

            // Comparar el mes de la factura con el mes ingresado
            if (strcmp(factura_mes, mes) == 0) {
                ventas_encontradas++;

                // Buscar el cliente por cédula
                Cliente *cliente_encontrado = NULL;
                GList *c;
                for (c = clientes; c != NULL; c = c->next) {
                    Cliente *cliente = (Cliente *)c->data;
                    if (strcmp(cliente->cedula, factura->cedula_cliente) == 0) {
                        cliente_encontrado = cliente;
                        break;
                    }
                }

                // Obtener el nombre y apellido del cliente si se encontró
                const char *nombre_cliente = cliente_encontrado ? cliente_encontrado->nombre : "Desconocido";
                const char *apellido_cliente = cliente_encontrado ? cliente_encontrado->apellido : "Desconocido";

                // Agregar la información de la factura al string
                g_string_append_printf(text, 
                    "Factura N#: %d\n"
                    "Fecha: %s\n"
                    "Cliente: %s %s\n"
                    "Cedula: %s\n"
                    "Subtotal: %.2f\n"
                    "IVA: %.2f\n"
                    "Total: %.2f\n\n",
                    ventas_encontradas,
                    factura->fecha,
                    nombre_cliente, apellido_cliente,
                    factura->cedula_cliente,
                    factura->subtotal,
                    factura->iva,
                    factura->total);
            }
        }

        // Mostrar un mensaje si no se encontraron ventas
        if (ventas_encontradas == 0) {
            g_string_append(text, "No se encontraron ventas para el mes ingresado.");
        }

        // Insertar el texto en el buffer
        gtk_text_buffer_set_text(buffer, text->str, -1);

        // Liberar la memoria del string
        g_string_free(text, TRUE);

        // Mostrar la ventana
        gtk_widget_show_all(window_ventas);
    }), window);

    // Asignar el campo de entrada como dato de la ventana
    g_object_set_data(G_OBJECT(window), "entry_mes", entry_mes);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Modificar Producto"
void on_modificar_producto_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *entry_codigo, *entry_nombre, *entry_cantidad, *entry_precio_bs, *entry_precio_pesos, *entry_precio_dolares, *entry_precio_euros;
    GtkWidget *button_buscar, *button_guardar;

    // Crear una nueva ventana para "Modificar Producto"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Modificar Producto");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para el código del producto
    label = gtk_label_new("Codigo del Producto:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    entry_codigo = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_codigo, 1, 0, 1, 1);

    // Botón para buscar el producto
    button_buscar = gtk_button_new_with_label("Buscar Producto");
    gtk_grid_attach(GTK_GRID(grid), button_buscar, 0, 1, 2, 1);

    // Conectar la señal del botón "Buscar Producto"
    g_signal_connect(button_buscar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_codigo = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_codigo"));
        const char *codigo_str = gtk_entry_get_text(entry_codigo);
        int codigo = atoi(codigo_str);

        // Buscar el producto en la lista
        GList *l;
        Producto *producto_encontrado = NULL;
        for (l = productos; l != NULL; l = l->next) {
            Producto *producto = (Producto *)l->data;
            if (producto->codigo == codigo) {
                producto_encontrado = producto;
                break;
            }
        }

        if (producto_encontrado == NULL) {
            // Mostrar un mensaje de error si el producto no existe
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Producto no encontrado");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Mostrar los datos del producto en los campos de entrada
        GtkEntry *entry_nombre = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_nombre"));
        GtkEntry *entry_cantidad = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_cantidad"));
        GtkEntry *entry_precio_bs = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_precio_bs"));
        GtkEntry *entry_precio_pesos = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_precio_pesos"));
        GtkEntry *entry_precio_dolares = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_precio_dolares"));
        GtkEntry *entry_precio_euros = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_precio_euros"));

        gtk_entry_set_text(entry_nombre, producto_encontrado->nombre);
        gtk_entry_set_text(entry_cantidad, g_strdup_printf("%d", producto_encontrado->cantidad));
        gtk_entry_set_text(entry_precio_bs, g_strdup_printf("%.2f", producto_encontrado->precio_bs));
        gtk_entry_set_text(entry_precio_pesos, g_strdup_printf("%.2f", producto_encontrado->precio_pesos));
        gtk_entry_set_text(entry_precio_dolares, g_strdup_printf("%.2f", producto_encontrado->precio_dolares));
        gtk_entry_set_text(entry_precio_euros, g_strdup_printf("%.2f", producto_encontrado->precio_euros));
    }), window);

    // Campo de entrada para el nombre del producto
    label = gtk_label_new("Nombre del Producto:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
    entry_nombre = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_nombre, 1, 2, 1, 1);

    // Campo de entrada para la cantidad del producto
    label = gtk_label_new("Cantidad Disponible:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);
    entry_cantidad = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_cantidad, 1, 3, 1, 1);

    // Campo de entrada para el precio en Bs
    label = gtk_label_new("Precio en Bs:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 4, 1, 1);
    entry_precio_bs = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_precio_bs, 1, 4, 1, 1);

    // Campo de entrada para el precio en Pesos
    label = gtk_label_new("Precio en Pesos:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 5, 1, 1);
    entry_precio_pesos = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_precio_pesos, 1, 5, 1, 1);

    // Campo de entrada para el precio en Dólares
    label = gtk_label_new("Precio en Dolares:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 6, 1, 1);
    entry_precio_dolares = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_precio_dolares, 1, 6, 1, 1);

    // Campo de entrada para el precio en Euros
    label = gtk_label_new("Precio en Euros:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 7, 1, 1);
    entry_precio_euros = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_precio_euros, 1, 7, 1, 1);

    // Botón para guardar los cambios
    button_guardar = gtk_button_new_with_label("Guardar Cambios");
    gtk_grid_attach(GTK_GRID(grid), button_guardar, 0, 8, 2, 1);

    // Conectar la señal del botón "Guardar Cambios"
    g_signal_connect(button_guardar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_codigo = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_codigo"));
        GtkEntry *entry_nombre = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_nombre"));
        GtkEntry *entry_cantidad = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_cantidad"));
        GtkEntry *entry_precio_bs = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_precio_bs"));
        GtkEntry *entry_precio_pesos = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_precio_pesos"));
        GtkEntry *entry_precio_dolares = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_precio_dolares"));
        GtkEntry *entry_precio_euros = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_precio_euros"));

        // Obtener los valores de los campos de entrada
        const char *codigo_str = gtk_entry_get_text(entry_codigo);
        const char *nombre = gtk_entry_get_text(entry_nombre);
        const char *cantidad_str = gtk_entry_get_text(entry_cantidad);
        const char *precio_bs_str = gtk_entry_get_text(entry_precio_bs);
        const char *precio_pesos_str = gtk_entry_get_text(entry_precio_pesos);
        const char *precio_dolares_str = gtk_entry_get_text(entry_precio_dolares);
        const char *precio_euros_str = gtk_entry_get_text(entry_precio_euros);

        // Convertir los valores a números
        int codigo = atoi(codigo_str);
        int cantidad = atoi(cantidad_str);
        float precio_bs = atof(precio_bs_str);
        float precio_pesos = atof(precio_pesos_str);
        float precio_dolares = atof(precio_dolares_str);
        float precio_euros = atof(precio_euros_str);

        // Buscar el producto en la lista
        GList *l;
        Producto *producto_encontrado = NULL;
        for (l = productos; l != NULL; l = l->next) {
            Producto *producto = (Producto *)l->data;
            if (producto->codigo == codigo) {
                producto_encontrado = producto;
                break;
            }
        }

        if (producto_encontrado == NULL) {
            // Mostrar un mensaje de error si el producto no existe
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Producto no encontrado");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Modificar el producto
        strncpy(producto_encontrado->nombre, nombre, sizeof(producto_encontrado->nombre));
        producto_encontrado->cantidad = cantidad;
        producto_encontrado->precio_bs = precio_bs;
        producto_encontrado->precio_pesos = precio_pesos;
        producto_encontrado->precio_dolares = precio_dolares;
        producto_encontrado->precio_euros = precio_euros;

        // Mostrar un mensaje de éxito
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Producto modificado exitosamente");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Cerrar la ventana después de guardar
        gtk_widget_destroy(GTK_WIDGET(data));
    }), window);

    // Asignar los campos de entrada como datos de la ventana
    g_object_set_data(G_OBJECT(window), "entry_codigo", entry_codigo);
    g_object_set_data(G_OBJECT(window), "entry_nombre", entry_nombre);
    g_object_set_data(G_OBJECT(window), "entry_cantidad", entry_cantidad);
    g_object_set_data(G_OBJECT(window), "entry_precio_bs", entry_precio_bs);
    g_object_set_data(G_OBJECT(window), "entry_precio_pesos", entry_precio_pesos);
    g_object_set_data(G_OBJECT(window), "entry_precio_dolares", entry_precio_dolares);
    g_object_set_data(G_OBJECT(window), "entry_precio_euros", entry_precio_euros);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Eliminar Producto"
void on_eliminar_producto_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *entry_codigo;
    GtkWidget *button_eliminar;

    // Crear una nueva ventana para "Eliminar Producto"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Eliminar Producto");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para el código del producto
    label = gtk_label_new("Codigo del Producto:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    entry_codigo = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_codigo, 1, 0, 1, 1);

    // Botón para eliminar el producto
    button_eliminar = gtk_button_new_with_label("Eliminar Producto");
    gtk_grid_attach(GTK_GRID(grid), button_eliminar, 0, 1, 2, 1);

    // Conectar la señal del botón "Eliminar Producto"
    g_signal_connect(button_eliminar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_codigo = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_codigo"));
        const char *codigo_str = gtk_entry_get_text(entry_codigo);
        int codigo = atoi(codigo_str);

        // Buscar el producto en la lista
        GList *l;
        Producto *producto_encontrado = NULL;
        for (l = productos; l != NULL; l = l->next) {
            Producto *producto = (Producto *)l->data;
            if (producto->codigo == codigo) {
                producto_encontrado = producto;
                break;
            }
        }

        if (producto_encontrado == NULL) {
            // Mostrar un mensaje de error si el producto no existe
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Producto no encontrado");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Eliminar el producto de la lista
        productos = g_list_remove(productos, producto_encontrado);
        g_free(producto_encontrado);

        // Mostrar un mensaje de éxito
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Producto eliminado exitosamente");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Cerrar la ventana después de eliminar
        gtk_widget_destroy(GTK_WIDGET(data));
    }), window);

    // Asignar el campo de entrada como dato de la ventana
    g_object_set_data(G_OBJECT(window), "entry_codigo", entry_codigo);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Mostrar Productos"
void on_mostrar_productos_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *scroll;
    GtkWidget *view;
    GtkTextBuffer *buffer;

    // Crear una nueva ventana para "Mostrar Productos"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mostrar Productos");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    
    // Crear un área de texto con scroll
    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_hexpand(scroll, TRUE);
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_grid_attach(GTK_GRID(grid), scroll, 0, 0, 1, 1);

    view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
    gtk_container_add(GTK_CONTAINER(scroll), view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

    // Mostrar los productos en el área de texto
    GList *l;
    for (l = productos; l != NULL; l = l->next) {
        Producto *producto = (Producto *)l->data;

        // Formatear el texto del producto
        gchar *text = g_strdup_printf(
            "Codigo: %d\n"
            "Nombre: %s\n"
            "Cantidad: %d\n"
            "Precio en Bs: %.2f\n"
            "Precio en Pesos: %.2f\n"
            "Precio en Dolares: %.2f\n"
            "Precio en Euros: %.2f\n\n",
            producto->codigo,
            producto->nombre,
            producto->cantidad,
            producto->precio_bs,
            producto->precio_pesos,
            producto->precio_dolares,
            producto->precio_euros);

        // Insertar el texto en el buffer
        gtk_text_buffer_insert_at_cursor(buffer, text, -1);

        // Liberar la memoria asignada para el texto
        g_free(text);
    }

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Clientes"
void on_clientes_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button_crear, *button_modificar, *button_eliminar, *button_mostrar;

    // Crear una nueva ventana para el módulo de clientes
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Modulo de Clientes");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    // Crear un grid para organizar los botones
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Botón "Crear Cliente"
    button_crear = gtk_button_new_with_label("Crear Cliente");
    g_signal_connect(button_crear, "clicked", G_CALLBACK(on_crear_cliente_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_crear, 0, 0, 1, 1);

    // Botón "Modificar Cliente"
    button_modificar = gtk_button_new_with_label("Modificar Cliente");
    g_signal_connect(button_modificar, "clicked", G_CALLBACK(on_modificar_cliente_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_modificar, 0, 1, 1, 1);

    // Botón "Eliminar Cliente"
    button_eliminar = gtk_button_new_with_label("Eliminar Cliente");
    g_signal_connect(button_eliminar, "clicked", G_CALLBACK(on_eliminar_cliente_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_eliminar, 0, 2, 1, 1);

    // Botón "Mostrar Clientes"
    button_mostrar = gtk_button_new_with_label("Mostrar Clientes");
    g_signal_connect(button_mostrar, "clicked", G_CALLBACK(on_mostrar_clientes_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_mostrar, 0, 3, 1, 1);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Crear Cliente"
void on_crear_cliente_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *entry_nombre, *entry_apellido, *entry_cedula, *entry_telefono, *entry_direccion;
    GtkWidget *button_guardar;

    // Crear una nueva ventana para "Crear Cliente"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Crear Cliente");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para el nombre del cliente
    label = gtk_label_new("Nombre del Cliente:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    entry_nombre = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_nombre, 1, 0, 1, 1);

    // Campo de entrada para el apellido del cliente
    label = gtk_label_new("Apellido del Cliente:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
    entry_apellido = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_apellido, 1, 1, 1, 1);

    // Campo de entrada para la cédula del cliente
    label = gtk_label_new("Cedula del Cliente:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
    entry_cedula = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_cedula, 1, 2, 1, 1);

    // Campo de entrada para el teléfono del cliente
    label = gtk_label_new("Telefono del Cliente:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);
    entry_telefono = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_telefono, 1, 3, 1, 1);

    // Campo de entrada para la dirección del cliente
    label = gtk_label_new("Direccion del Cliente:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 4, 1, 1);
    entry_direccion = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_direccion, 1, 4, 1, 1);

    // Botón para guardar el cliente
    button_guardar = gtk_button_new_with_label("Guardar Cliente");
    gtk_grid_attach(GTK_GRID(grid), button_guardar, 0, 5, 2, 1);

    // Conectar la señal del botón "Guardar Cliente"
    g_signal_connect(button_guardar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_nombre = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_nombre"));
        GtkEntry *entry_apellido = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_apellido"));
        GtkEntry *entry_cedula = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_cedula"));
        GtkEntry *entry_telefono = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_telefono"));
        GtkEntry *entry_direccion = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_direccion"));

        // Obtener los valores de los campos de entrada
        const char *nombre = gtk_entry_get_text(entry_nombre);
        const char *apellido = gtk_entry_get_text(entry_apellido);
        const char *cedula = gtk_entry_get_text(entry_cedula);
        const char *telefono = gtk_entry_get_text(entry_telefono);
        const char *direccion = gtk_entry_get_text(entry_direccion);

        // Crear un nuevo cliente
        Cliente *cliente = g_new(Cliente, 1);
        strncpy(cliente->nombre, nombre, sizeof(cliente->nombre));
        strncpy(cliente->apellido, apellido, sizeof(cliente->apellido));
        strncpy(cliente->cedula, cedula, sizeof(cliente->cedula));
        strncpy(cliente->telefono, telefono, sizeof(cliente->telefono));
        strncpy(cliente->direccion, direccion, sizeof(cliente->direccion));

        // Agregar el cliente a la lista
        clientes = g_list_append(clientes, cliente);

        // Mostrar un mensaje de éxito
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Cliente creado exitosamente");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Cerrar la ventana después de guardar
        gtk_widget_destroy(GTK_WIDGET(data));
    }), window);

    // Asignar los campos de entrada como datos de la ventana
    g_object_set_data(G_OBJECT(window), "entry_nombre", entry_nombre);
    g_object_set_data(G_OBJECT(window), "entry_apellido", entry_apellido);
    g_object_set_data(G_OBJECT(window), "entry_cedula", entry_cedula);
    g_object_set_data(G_OBJECT(window), "entry_telefono", entry_telefono);
    g_object_set_data(G_OBJECT(window), "entry_direccion", entry_direccion);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Modificar Cliente"
void on_modificar_cliente_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *entry_cedula, *entry_nombre, *entry_apellido, *entry_telefono, *entry_direccion;
    GtkWidget *button_buscar, *button_guardar;

    // Crear una nueva ventana para "Modificar Cliente"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Modificar Cliente");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para la cédula del cliente
    label = gtk_label_new("Cedula del Cliente:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    entry_cedula = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_cedula, 1, 0, 1, 1);

    // Botón para buscar el cliente
    button_buscar = gtk_button_new_with_label("Buscar Cliente");
    gtk_grid_attach(GTK_GRID(grid), button_buscar, 0, 1, 2, 1);

    // Conectar la señal del botón "Buscar Cliente"
    g_signal_connect(button_buscar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_cedula = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_cedula"));
        const char *cedula = gtk_entry_get_text(entry_cedula);

        // Buscar el cliente en la lista
        GList *l;
        Cliente *cliente_encontrado = NULL;
        for (l = clientes; l != NULL; l = l->next) {
            Cliente *cliente = (Cliente *)l->data;
            if (strcmp(cliente->cedula, cedula) == 0) {
                cliente_encontrado = cliente;
                break;
            }
        }

        if (cliente_encontrado == NULL) {
            // Mostrar un mensaje de error si el cliente no existe
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Cliente no encontrado");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Mostrar los datos del cliente en los campos de entrada
        GtkEntry *entry_nombre = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_nombre"));
        GtkEntry *entry_apellido = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_apellido"));
        GtkEntry *entry_telefono = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_telefono"));
        GtkEntry *entry_direccion = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_direccion"));

        gtk_entry_set_text(entry_nombre, cliente_encontrado->nombre);
        gtk_entry_set_text(entry_apellido, cliente_encontrado->apellido);
        gtk_entry_set_text(entry_telefono, cliente_encontrado->telefono);
        gtk_entry_set_text(entry_direccion, cliente_encontrado->direccion);
    }), window);

    // Campo de entrada para el nombre del cliente
    label = gtk_label_new("Nombre del Cliente:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
    entry_nombre = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_nombre, 1, 2, 1, 1);

    // Campo de entrada para el apellido del cliente
    label = gtk_label_new("Apellido del Cliente:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);
    entry_apellido = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_apellido, 1, 3, 1, 1);

    // Campo de entrada para el teléfono del cliente
    label = gtk_label_new("Telefono del Cliente:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 4, 1, 1);
    entry_telefono = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_telefono, 1, 4, 1, 1);

    // Campo de entrada para la dirección del cliente
    label = gtk_label_new("Direccion del Cliente:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 5, 1, 1);
    entry_direccion = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_direccion, 1, 5, 1, 1);

    // Botón para guardar los cambios
    button_guardar = gtk_button_new_with_label("Guardar Cambios");
    gtk_grid_attach(GTK_GRID(grid), button_guardar, 0, 6, 2, 1);

    // Conectar la señal del botón "Guardar Cambios"
    g_signal_connect(button_guardar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_cedula = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_cedula"));
        GtkEntry *entry_nombre = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_nombre"));
        GtkEntry *entry_apellido = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_apellido"));
        GtkEntry *entry_telefono = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_telefono"));
        GtkEntry *entry_direccion = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_direccion"));

        // Obtener los valores de los campos de entrada
        const char *cedula = gtk_entry_get_text(entry_cedula);
        const char *nombre = gtk_entry_get_text(entry_nombre);
        const char *apellido = gtk_entry_get_text(entry_apellido);
        const char *telefono = gtk_entry_get_text(entry_telefono);
        const char *direccion = gtk_entry_get_text(entry_direccion);

        // Buscar el cliente en la lista
        GList *l;
        Cliente *cliente_encontrado = NULL;
        for (l = clientes; l != NULL; l = l->next) {
            Cliente *cliente = (Cliente *)l->data;
            if (strcmp(cliente->cedula, cedula) == 0) {
                cliente_encontrado = cliente;
                break;
            }
        }

        if (cliente_encontrado == NULL) {
            // Mostrar un mensaje de error si el cliente no existe
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Cliente no encontrado");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Modificar el cliente
        strncpy(cliente_encontrado->nombre, nombre, sizeof(cliente_encontrado->nombre));
        strncpy(cliente_encontrado->apellido, apellido, sizeof(cliente_encontrado->apellido));
        strncpy(cliente_encontrado->telefono, telefono, sizeof(cliente_encontrado->telefono));
        strncpy(cliente_encontrado->direccion, direccion, sizeof(cliente_encontrado->direccion));

        // Mostrar un mensaje de éxito
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Cliente modificado exitosamente");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Cerrar la ventana después de guardar
        gtk_widget_destroy(GTK_WIDGET(data));
    }), window);

    // Asignar los campos de entrada como datos de la ventana
    g_object_set_data(G_OBJECT(window), "entry_cedula", entry_cedula);
    g_object_set_data(G_OBJECT(window), "entry_nombre", entry_nombre);
    g_object_set_data(G_OBJECT(window), "entry_apellido", entry_apellido);
    g_object_set_data(G_OBJECT(window), "entry_telefono", entry_telefono);
    g_object_set_data(G_OBJECT(window), "entry_direccion", entry_direccion);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Eliminar Cliente"
void on_eliminar_cliente_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *entry_cedula;
    GtkWidget *button_eliminar;

    // Crear una nueva ventana para "Eliminar Cliente"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Eliminar Cliente");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para la cédula del cliente
    label = gtk_label_new("Cedula del Cliente:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    entry_cedula = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_cedula, 1, 0, 1, 1);

    // Botón para eliminar el cliente
    button_eliminar = gtk_button_new_with_label("Eliminar Cliente");
    gtk_grid_attach(GTK_GRID(grid), button_eliminar, 0, 1, 2, 1);

    // Conectar la señal del botón "Eliminar Cliente"
    g_signal_connect(button_eliminar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_cedula = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_cedula"));
        const char *cedula = gtk_entry_get_text(entry_cedula);

        // Buscar el cliente en la lista
        GList *l;
        Cliente *cliente_encontrado = NULL;
        for (l = clientes; l != NULL; l = l->next) {
            Cliente *cliente = (Cliente *)l->data;
            if (strcmp(cliente->cedula, cedula) == 0) {
                cliente_encontrado = cliente;
                break;
            }
        }

        if (cliente_encontrado == NULL) {
            // Mostrar un mensaje de error si el cliente no existe
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Cliente no encontrado");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Eliminar el cliente de la lista
        clientes = g_list_remove(clientes, cliente_encontrado);
        g_free(cliente_encontrado);

        // Mostrar un mensaje de éxito
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Cliente eliminado exitosamente");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Cerrar la ventana después de eliminar
        gtk_widget_destroy(GTK_WIDGET(data));
    }), window);

    // Asignar el campo de entrada como dato de la ventana
    g_object_set_data(G_OBJECT(window), "entry_cedula", entry_cedula);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Mostrar Clientes"
void on_mostrar_clientes_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *scroll;
    GtkWidget *view;
    GtkTextBuffer *buffer;

    // Crear una nueva ventana para "Mostrar Clientes"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mostrar Clientes");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Crear un área de texto con scroll
    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_hexpand(scroll, TRUE);
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_grid_attach(GTK_GRID(grid), scroll, 0, 0, 1, 1);

    view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
    gtk_container_add(GTK_CONTAINER(scroll), view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

    // Mostrar los clientes en el área de texto
    GList *l;
    for (l = clientes; l != NULL; l = l->next) {
        Cliente *cliente = (Cliente *)l->data;

        // Formatear el texto del cliente
        gchar *text = g_strdup_printf(
            "Nombre: %s\n"
            "Apellido: %s\n"
            "Cedula: %s\n"
            "Telefono: %s\n"
            "Direccion: %s\n\n",
            cliente->nombre,
            cliente->apellido,
            cliente->cedula,
            cliente->telefono,
            cliente->direccion);

        // Insertar el texto en el buffer
        gtk_text_buffer_insert_at_cursor(buffer, text, -1);

        // Liberar la memoria asignada para el texto
        g_free(text);
    }

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Facturas"
void on_facturas_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button_crear, *button_modificar, *button_eliminar, *button_mostrar;

    // Crear una nueva ventana para el módulo de facturas
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Modulo de Facturas");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    // Crear un grid para organizar los botones
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Botón "Crear Factura"
    button_crear = gtk_button_new_with_label("Crear Factura");
    g_signal_connect(button_crear, "clicked", G_CALLBACK(on_crear_factura_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_crear, 0, 0, 1, 1);

    // Botón "Modificar Factura"
    button_modificar = gtk_button_new_with_label("Modificar Factura");
    g_signal_connect(button_modificar, "clicked", G_CALLBACK(on_modificar_factura_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_modificar, 0, 1, 1, 1);

    // Botón "Eliminar Factura"
    button_eliminar = gtk_button_new_with_label("Eliminar Factura");
    g_signal_connect(button_eliminar, "clicked", G_CALLBACK(on_eliminar_factura_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_eliminar, 0, 2, 1, 1);

    // Botón "Mostrar Facturas"
    button_mostrar = gtk_button_new_with_label("Mostrar Facturas");
    g_signal_connect(button_mostrar, "clicked", G_CALLBACK(on_mostrar_facturas_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_mostrar, 0, 3, 1, 1);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Crear Factura"
void on_crear_factura_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *entry_fecha, *entry_cedula, *entry_cantidad_productos;
    GtkWidget *button_guardar;

    // Crear una nueva ventana para "Crear Factura"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Crear Factura");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para la fecha
    label = gtk_label_new("Fecha:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    entry_fecha = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_fecha, 1, 0, 1, 1);

    // Campo de entrada para la cédula del cliente
    label = gtk_label_new("Cedula del Cliente:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
    entry_cedula = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_cedula, 1, 1, 1, 1);

    // Campo de entrada para la cantidad de productos
    label = gtk_label_new("Cantidad de Productos:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
    entry_cantidad_productos = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_cantidad_productos, 1, 2, 1, 1);

    // Botón para guardar la factura
    button_guardar = gtk_button_new_with_label("Guardar Factura");
    gtk_grid_attach(GTK_GRID(grid), button_guardar, 0, 3, 2, 1);

    // Conectar la señal del botón "Guardar Factura"
    g_signal_connect(button_guardar, "clicked", G_CALLBACK(on_crear_factura_guardar), window);

    // Asignar los campos de entrada como datos de la ventana
    g_object_set_data(G_OBJECT(window), "entry_fecha", entry_fecha);
    g_object_set_data(G_OBJECT(window), "entry_cedula", entry_cedula);
    g_object_set_data(G_OBJECT(window), "entry_cantidad_productos", entry_cantidad_productos);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Guardar Factura"
void on_crear_factura_guardar(GtkButton *button, gpointer user_data) {
    GtkWidget *window = GTK_WIDGET(user_data);
    GtkEntry *entry_fecha = GTK_ENTRY(g_object_get_data(G_OBJECT(window), "entry_fecha"));
    GtkEntry *entry_cedula = GTK_ENTRY(g_object_get_data(G_OBJECT(window), "entry_cedula"));
    GtkEntry *entry_cantidad_productos = GTK_ENTRY(g_object_get_data(G_OBJECT(window), "entry_cantidad_productos"));

    // Obtener los valores de los campos de entrada
    const char *fecha = gtk_entry_get_text(entry_fecha);
    const char *cedula = gtk_entry_get_text(entry_cedula);
    const char *cantidad_productos_str = gtk_entry_get_text(entry_cantidad_productos);

    // Convertir la cantidad de productos a un entero
    int cantidad_productos = atoi(cantidad_productos_str);

    // Verificar si el cliente existe
    GList *l;
    Cliente *cliente_encontrado = NULL;
    for (l = clientes; l != NULL; l = l->next) {
        Cliente *cliente = (Cliente *)l->data;
        if (strcmp(cliente->cedula, cedula) == 0) {
            cliente_encontrado = cliente;
            break;
        }
    }

    if (cliente_encontrado == NULL) {
        // Mostrar un mensaje de error si el cliente no existe
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "No se encuentra el cliente");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Crear una nueva factura
    Factura *factura = g_new(Factura, 1);
    strncpy(factura->fecha, fecha, sizeof(factura->fecha));
    strncpy(factura->cedula_cliente, cedula, sizeof(factura->cedula_cliente));
    factura->items = NULL;
    factura->subtotal = 0;
    factura->iva = 0;
    factura->total = 0;

    // Agregar productos a la factura
    for (int i = 0; i < cantidad_productos; i++) {
        GtkWidget *dialog = gtk_dialog_new_with_buttons("Agregar Producto", GTK_WINDOW(window), GTK_DIALOG_MODAL, "Aceptar", GTK_RESPONSE_ACCEPT, NULL);
        GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
        GtkWidget *grid = gtk_grid_new();
        gtk_container_add(GTK_CONTAINER(content_area), grid);

        // Campo de entrada para el código del producto
        GtkWidget *label_codigo = gtk_label_new("Codigo del Producto:");
        gtk_grid_attach(GTK_GRID(grid), label_codigo, 0, 0, 1, 1);
        GtkWidget *entry_codigo = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), entry_codigo, 1, 0, 1, 1);

        // Campo de entrada para la cantidad del producto
        GtkWidget *label_cantidad = gtk_label_new("Cantidad del Producto:");
        gtk_grid_attach(GTK_GRID(grid), label_cantidad, 0, 1, 1, 1);
        GtkWidget *entry_cantidad = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), entry_cantidad, 1, 1, 1, 1);

        // Mostrar el diálogo
        gtk_widget_show_all(dialog);
        gint response = gtk_dialog_run(GTK_DIALOG(dialog));

        if (response == GTK_RESPONSE_ACCEPT) {
            const char *codigo_str = gtk_entry_get_text(GTK_ENTRY(entry_codigo));
            const char *cantidad_str = gtk_entry_get_text(GTK_ENTRY(entry_cantidad));

            int codigo = atoi(codigo_str);
            int cantidad = atoi(cantidad_str);

            // Buscar el producto en la lista
            GList *l;
            Producto *producto_encontrado = NULL;
            for (l = productos; l != NULL; l = l->next) {
                Producto *producto = (Producto *)l->data;
                if (producto->codigo == codigo) {
                    producto_encontrado = producto;
                    break;
                }
            }

            if (producto_encontrado == NULL) {
                // Mostrar un mensaje de error si el producto no existe
                GtkWidget *dialog_error = gtk_message_dialog_new(GTK_WINDOW(dialog), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Producto no encontrado");
                gtk_dialog_run(GTK_DIALOG(dialog_error));
                gtk_widget_destroy(dialog_error);
                i--; // Repetir la iteración para este producto
                continue;
            }

            // Crear un ítem de factura
            ItemFactura *item = g_new(ItemFactura, 1);
            item->codigo_producto = codigo;
            item->cantidad = cantidad;
            item->precio_unitario = producto_encontrado->precio_bs; // Usar el precio en Bs

            // Agregar el ítem a la factura
            factura->items = g_list_append(factura->items, item);

            // Actualizar el subtotal de la factura
            factura->subtotal += item->cantidad * item->precio_unitario;
        }

        gtk_widget_destroy(dialog);
    }

    // Calcular el IVA (16%)
    factura->iva = factura->subtotal * 0.16;

    // Calcular el total
    factura->total = factura->subtotal + factura->iva;

    // Agregar la factura a la lista
    facturas = g_list_append(facturas, factura);

    // Mostrar los datos de la factura en la consola
    printf("Factura creada:\n");
    printf("Fecha: %s\n", factura->fecha);
    printf("Cedula del Cliente: %s\n", factura->cedula_cliente);
    printf("Subtotal: %.2f\n", factura->subtotal);
    printf("IVA: %.2f\n", factura->iva);
    printf("Total: %.2f\n", factura->total);

    // Cerrar la ventana después de guardar
    gtk_widget_destroy(window);
}

// Función para manejar el clic en el botón "Modificar Factura"
void on_modificar_factura_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *entry_fecha, *entry_cedula, *entry_cantidad_productos;
    GtkWidget *button_buscar, *button_guardar;

    // Crear una nueva ventana para "Modificar Factura"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Modificar Factura");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para la fecha
    label = gtk_label_new("Fecha:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    entry_fecha = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_fecha, 1, 0, 1, 1);

    // Campo de entrada para la cédula del cliente
    label = gtk_label_new("Cedula del Cliente:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
    entry_cedula = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_cedula, 1, 1, 1, 1);

    // Botón para buscar la factura
    button_buscar = gtk_button_new_with_label("Buscar Factura");
    gtk_grid_attach(GTK_GRID(grid), button_buscar, 0, 2, 2, 1);

    // Conectar la señal del botón "Buscar Factura"
    g_signal_connect(button_buscar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_fecha = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_fecha"));
        GtkEntry *entry_cedula = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_cedula"));
        const char *fecha = gtk_entry_get_text(entry_fecha);
        const char *cedula = gtk_entry_get_text(entry_cedula);

        // Buscar la factura en la lista
        GList *l;
        Factura *factura_encontrada = NULL;
        for (l = facturas; l != NULL; l = l->next) {
            Factura *factura = (Factura *)l->data;
            if (strcmp(factura->fecha, fecha) == 0 && strcmp(factura->cedula_cliente, cedula) == 0) {
                factura_encontrada = factura;
                break;
            }
        }

        if (factura_encontrada == NULL) {
            // Mostrar un mensaje de error si la factura no existe
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Factura no encontrada");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Mostrar los datos de la factura en los campos de entrada
        GtkEntry *entry_cantidad_productos = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_cantidad_productos"));
        gtk_entry_set_text(entry_cantidad_productos, g_strdup_printf("%d", g_list_length(factura_encontrada->items)));
    }), window);

    // Campo de entrada para la cantidad de productos
    label = gtk_label_new("Cantidad de Productos:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
    entry_cantidad_productos = gtk_entry_new();  // Asegurar la declaración aquí
    gtk_grid_attach(GTK_GRID(grid), entry_cantidad_productos, 1, 2, 1, 1);

    // Botón para guardar los cambios
    button_guardar = gtk_button_new_with_label("Guardar Cambios");
    gtk_grid_attach(GTK_GRID(grid), button_guardar, 0, 4, 2, 1);

    // Conectar la señal del botón "Guardar Cambios"
    g_signal_connect(button_guardar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_fecha = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_fecha"));
        GtkEntry *entry_cedula = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_cedula"));
        GtkEntry *entry_cantidad_productos = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_cantidad_productos"));

        // Obtener los valores de los campos de entrada
        const char *fecha = gtk_entry_get_text(entry_fecha);
        const char *cedula = gtk_entry_get_text(entry_cedula);
        const char *cantidad_productos_str = gtk_entry_get_text(entry_cantidad_productos);

        // Convertir la cantidad de productos a un entero
        int cantidad_productos = atoi(cantidad_productos_str);

        // Buscar la factura en la lista
        GList *l;
        Factura *factura_encontrada = NULL;
        for (l = facturas; l != NULL; l = l->next) {
            Factura *factura = (Factura *)l->data;
            if (strcmp(factura->fecha, fecha) == 0 && strcmp(factura->cedula_cliente, cedula) == 0) {
                factura_encontrada = factura;
                break;
            }
        }

        if (factura_encontrada == NULL) {
            // Mostrar un mensaje de error si la factura no existe
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Factura no encontrada");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Modificar la factura
        factura_encontrada->items = NULL;
        factura_encontrada->subtotal = 0;
        factura_encontrada->iva = 0;
        factura_encontrada->total = 0;

        // Agregar productos a la factura
        for (int i = 0; i < cantidad_productos; i++) {
            GtkWidget *dialog = gtk_dialog_new_with_buttons("Agregar Producto", GTK_WINDOW(data), GTK_DIALOG_MODAL, "Aceptar", GTK_RESPONSE_ACCEPT, NULL);
            GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
            GtkWidget *grid = gtk_grid_new();
            gtk_container_add(GTK_CONTAINER(content_area), grid);

            // Campo de entrada para el código del producto
            GtkWidget *label_codigo = gtk_label_new("Codigo del Producto:");
            gtk_grid_attach(GTK_GRID(grid), label_codigo, 0, 0, 1, 1);
            GtkWidget *entry_codigo = gtk_entry_new();
            gtk_grid_attach(GTK_GRID(grid), entry_codigo, 1, 0, 1, 1);

            // Campo de entrada para la cantidad del producto
            GtkWidget *label_cantidad = gtk_label_new("Cantidad del Producto:");
            gtk_grid_attach(GTK_GRID(grid), label_cantidad, 0, 1, 1, 1);
            GtkWidget *entry_cantidad = gtk_entry_new();
            gtk_grid_attach(GTK_GRID(grid), entry_cantidad, 1, 1, 1, 1);

            // Mostrar el diálogo
            gtk_widget_show_all(dialog);
            gint response = gtk_dialog_run(GTK_DIALOG(dialog));

            if (response == GTK_RESPONSE_ACCEPT) {
                const char *codigo_str = gtk_entry_get_text(GTK_ENTRY(entry_codigo));
                const char *cantidad_str = gtk_entry_get_text(GTK_ENTRY(entry_cantidad));

                int codigo = atoi(codigo_str);
                int cantidad = atoi(cantidad_str);

                // Buscar el producto en la lista
                GList *l;
                Producto *producto_encontrado = NULL;
                for (l = productos; l != NULL; l = l->next) {
                    Producto *producto = (Producto *)l->data;
                    if (producto->codigo == codigo) {
                        producto_encontrado = producto;
                        break;
                    }
                }

                if (producto_encontrado == NULL) {
                    // Mostrar un mensaje de error si el producto no existe
                    GtkWidget *dialog_error = gtk_message_dialog_new(GTK_WINDOW(dialog), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Producto no encontrado");
                    gtk_dialog_run(GTK_DIALOG(dialog_error));
                    gtk_widget_destroy(dialog_error);
                    i--; // Repetir la iteración para este producto
                    continue;
                }

                // Crear un ítem de factura
                ItemFactura *item = g_new(ItemFactura, 1);
                item->codigo_producto = codigo;
                item->cantidad = cantidad;
                item->precio_unitario = producto_encontrado->precio_bs; // Usar el precio en Bs

                // Agregar el ítem a la factura
                factura_encontrada->items = g_list_append(factura_encontrada->items, item);

                // Actualizar el subtotal de la factura
                factura_encontrada->subtotal += item->cantidad * item->precio_unitario;
            }

            gtk_widget_destroy(dialog);
        }

        // Calcular el IVA (16%)
        factura_encontrada->iva = factura_encontrada->subtotal * 0.16;

        // Calcular el total
        factura_encontrada->total = factura_encontrada->subtotal + factura_encontrada->iva;

        // Mostrar un mensaje de éxito
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Factura modificada exitosamente");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Cerrar la ventana después de guardar
        gtk_widget_destroy(GTK_WIDGET(data));
    }), window);

    // Asignar los campos de entrada como datos de la ventana
    g_object_set_data(G_OBJECT(window), "entry_fecha", entry_fecha);
    g_object_set_data(G_OBJECT(window), "entry_cedula", entry_cedula);
    g_object_set_data(G_OBJECT(window), "entry_cantidad_productos", entry_cantidad_productos);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Eliminar Factura"
void on_eliminar_factura_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *entry_fecha, *entry_cedula;
    GtkWidget *button_eliminar;

    // Crear una nueva ventana para "Eliminar Factura"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Eliminar Factura");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada para la fecha
    label = gtk_label_new("Fecha:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    entry_fecha = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_fecha, 1, 0, 1, 1);

    // Campo de entrada para la cédula del cliente
    label = gtk_label_new("Cedula del Cliente:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
    entry_cedula = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_cedula, 1, 1, 1, 1);

    // Botón para eliminar la factura
    button_eliminar = gtk_button_new_with_label("Eliminar Factura");
    gtk_grid_attach(GTK_GRID(grid), button_eliminar, 0, 2, 2, 1);

    // Conectar la señal del botón "Eliminar Factura"
    g_signal_connect(button_eliminar, "clicked", G_CALLBACK(+[](GtkButton *button, gpointer data) {
        GtkEntry *entry_fecha = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_fecha"));
        GtkEntry *entry_cedula = GTK_ENTRY(g_object_get_data(G_OBJECT(data), "entry_cedula"));
        const char *fecha = gtk_entry_get_text(entry_fecha);
        const char *cedula = gtk_entry_get_text(entry_cedula);

        // Buscar la factura en la lista
        GList *l;
        Factura *factura_encontrada = NULL;
        for (l = facturas; l != NULL; l = l->next) {
            Factura *factura = (Factura *)l->data;
            if (strcmp(factura->fecha, fecha) == 0 && strcmp(factura->cedula_cliente, cedula) == 0) {
                factura_encontrada = factura;
                break;
            }
        }

        if (factura_encontrada == NULL) {
            // Mostrar un mensaje de error si la factura no existe
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Factura no encontrada");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }

        // Eliminar la factura de la lista
        facturas = g_list_remove(facturas, factura_encontrada);
        g_free(factura_encontrada);

        // Mostrar un mensaje de éxito
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Factura eliminada exitosamente");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Cerrar la ventana después de eliminar
        gtk_widget_destroy(GTK_WIDGET(data));
    }), window);

    // Asignar los campos de entrada como datos de la ventana
    g_object_set_data(G_OBJECT(window), "entry_fecha", entry_fecha);
    g_object_set_data(G_OBJECT(window), "entry_cedula", entry_cedula);

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

// Función para manejar el clic en el botón "Mostrar Facturas"
void on_mostrar_facturas_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *scroll;
    GtkWidget *view;
    GtkTextBuffer *buffer;

    // Crear una nueva ventana para "Mostrar Facturas"
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mostrar Facturas");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);

    // Crear un grid para organizar los elementos
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Crear un área de texto con scroll
    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_hexpand(scroll, TRUE);
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_grid_attach(GTK_GRID(grid), scroll, 0, 0, 1, 1);

    view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
    gtk_container_add(GTK_CONTAINER(scroll), view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

    // Verificar si hay facturas en la lista
    if (facturas == NULL) {
        gtk_text_buffer_set_text(buffer, "No hay facturas registradas.", -1);
    } else {
        // Crear un string para almacenar las facturas
        GString *text = g_string_new(NULL);

        // Recorrer la lista de facturas con un índice para numerarlas
        int numero_factura = 1;
        GList *l;
        for (l = facturas; l != NULL; l = l->next, numero_factura++) {
            Factura *factura = (Factura *)l->data;

            // Buscar el cliente por cédula
            Cliente *cliente_encontrado = NULL;
            GList *c;
            for (c = clientes; c != NULL; c = c->next) {
                Cliente *cliente = (Cliente *)c->data;
                if (strcmp(cliente->cedula, factura->cedula_cliente) == 0) {
                    cliente_encontrado = cliente;
                    break;
                }
            }

            // Obtener el nombre y apellido del cliente si se encontró
            const char *nombre_cliente = cliente_encontrado ? cliente_encontrado->nombre : "Desconocido";
            const char *apellido_cliente = cliente_encontrado ? cliente_encontrado->apellido : "Desconocido";

            // Agregar la información de la factura al string
            g_string_append_printf(text, 
                "Factura N#: %d\n"
                "Fecha: %s\n"
                "Cliente: %s %s\n"
                "Cedula: %s\n"
                "Subtotal: %.2f\n"
                "IVA: %.2f\n"
                "Total: %.2f\n\n",
                numero_factura,
                factura->fecha,
                nombre_cliente, apellido_cliente,
                factura->cedula_cliente,
                factura->subtotal,
                factura->iva,
                factura->total);
        }

        // Insertar el texto en el buffer
        gtk_text_buffer_set_text(buffer, text->str, -1);

        // Liberar la memoria del string
        g_string_free(text, TRUE);
    }

    // Mostrar la ventana
    gtk_widget_show_all(window);
}

