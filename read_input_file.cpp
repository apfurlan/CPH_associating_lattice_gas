#include <stdio.h>
#include <yaml.h>
#include <assert.h>

int main()
{
    FILE *file;
    yaml_parser_t parser;
    yaml_document_t document;
    yaml_node_t *node;
    int i = 1;

    file = fopen("input_model.yaml", "rb");
    assert(file);

    assert(yaml_parser_initialize(&parser));

    yaml_parser_set_input_file(&parser, file);

    if (!yaml_parser_load(&parser, &document)) {
        goto done;
    }

    // iterate through each node
    while(1) {
        node = yaml_document_get_node(&document, i);
        if(!node) break;
        if(node->type == YAML_SCALAR_NODE) {
            if (node->data.scalar.style == 1){ //assuming that the key is a string
                printf("%s: ", node->data.scalar.value);
                i++; 
                node = yaml_document_get_node(&document, i); //assuming that the value is stored as the next node
                if(!node) break;
                printf("%s (%d)\n", node->data.scalar.value, node->data.scalar.style); //value for each key and the type of value in the braces
            }
        }
        i++;
    }
    yaml_document_delete(&document);


    done:
      yaml_parser_delete(&parser); //to free memory
      assert(!fclose(file));

    return 0;
}