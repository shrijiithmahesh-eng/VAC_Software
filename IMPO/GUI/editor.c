char alphabet[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
int current_char_index = 0;
int buffer_index = 0;
int main() {
#define PIN_UP 0x01
#define PIN_LEFT 0x02
#define PIN_RIGHT 0x03
#define PIN_PWR 0x04
  // Check Rules.json for RAM limits before starting
    if (get_mem_usage() > 2048) {
        system_shutdown(); // Rule #1 Enforcement
    }
}

int read_input() {
    int key = hardware_bus_read();
    if (key == PIN_UP || key == PIN_LEFT || key == PIN_RIGHT) {
        return key; // Valid input
    } else {
        system_shutdown(); // Rule: Any other key = Shutdown
    }
}
void start_dpad_editor() {
    print_string("VAC-SELECT: [LEFT/RIGHT] to Browse, [UP] to Insert\n");

    while(1) {
        int key = read_input(); // This will shutdown if it's not 0x01, 0x02, or 0x03

        if (key == PIN_RIGHT) {
            current_char_index++;
            if (current_char_index > 37) current_char_index = 0;
            update_preview(alphabet[current_char_index]);
        } 
        else if (key == PIN_LEFT) {
            current_char_index--;
            if (current_char_index < 0) current_char_index = 37;
            update_preview(alphabet[current_char_index]);
        } 
        else if (key == PIN_UP) {
            // "Type" the letter into our buffer
            editor_buffer[buffer_index++] = alphabet[current_char_index];
            vga_print_char(alphabet[current_char_index], buffer_index, 5);
            
            // Auto-save if we reach the end of a line
            if (buffer_index >= 64) {
                save_to_mars(); 
            }
        }
    }
}
