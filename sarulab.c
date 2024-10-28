#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    char name[100];
    char category[100];
    char content[500];
} Blog;

void addBlog(Blog **blogs, int *count);
void deleteBlog(Blog **blogs, int *count, int id);
void displayBlogs(Blog *blogs, int count);
void searchBlog(Blog *blogs, int count, const char *name);
void writeBlogsToFile(Blog *blogs, int count);
void freeMemory(Blog **blogs);

int main() {
    Blog *blogs = NULL;
    int count = 0;
    int choice, id;
    char name[100];

    while (1) {
        printf("\nBlog Management System\n");
        printf("1. Add blog\n");
        printf("2. Delete blog (search by ID)\n");
        printf("3. Display all blogs\n");
        printf("4. Search blog (search by name)\n");
        printf("5. Write blogs to file and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                addBlog(&blogs, &count);
                break;
            case 2:
                printf("Enter Blog ID to delete: ");
                scanf("%d", &id);
                deleteBlog(&blogs, &count, id);
                break;
            case 3:
                displayBlogs(blogs, count);
                break;
            case 4:
                printf("Enter Blog name to search: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline character
                searchBlog(blogs, count, name);
                break;
            case 5:
                writeBlogsToFile(blogs, count);
                freeMemory(&blogs);
                printf("Blogs saved to file. Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}


void addBlog(Blog **blogs, int *count) {
    *blogs = realloc(*blogs, (*count + 1) * sizeof(Blog));
    if (*blogs == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    Blog *newBlog = &(*blogs)[*count];

    printf("Enter Blog ID: ");
    scanf("%d", &newBlog->id);
    getchar();

    printf("Enter Blog name: ");
    fgets(newBlog->name, sizeof(newBlog->name), stdin);
    newBlog->name[strcspn(newBlog->name, "\n")] = 0; 
    printf("Enter Blog Category: ");
    fgets(newBlog->category, sizeof(newBlog->category), stdin);
    newBlog->category[strcspn(newBlog->category, "\n")] = 0;

    printf("Enter Blog Content: ");
    fgets(newBlog->content, sizeof(newBlog->content), stdin);
    newBlog->content[strcspn(newBlog->content, "\n")] = 0; 

    (*count)++;
    printf("Blog added successfully!\n");
}


void deleteBlog(Blog **blogs, int *count, int id) {
    int found = 0;
    for (int i = 0; i < *count; i++) {
        if ((*blogs)[i].id == id) {
            found = 1;
            for (int j = i; j < *count - 1; j++) {
                (*blogs)[j] = (*blogs)[j + 1];
            }
            *blogs = realloc(*blogs, (*count - 1) * sizeof(Blog));
            if (*count > 1 && *blogs == NULL) {
                perror("Memory reallocation failed");
                exit(1);
            }
            (*count)--;
            printf("Blog with ID %d deleted successfully!\n", id);
            break;
        }
    }
    if (!found) {
        printf("Blog with ID %d not found.\n", id);
    }
}


void displayBlogs(Blog *blogs, int count) {
    if (count == 0) {
        printf("No blogs to display.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("\nBlog ID: %d\nname: %s\nCategory: %s\nContent: %s\n",
               blogs[i].id, blogs[i].name, blogs[i].category, blogs[i].content);
    }
}


void searchBlog(Blog *blogs, int count, const char *name) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(blogs[i].name, name) == 0) {
            printf("\nBlog ID: %d\nname: %s\nCategory: %s\nContent: %s\n",
                   blogs[i].id, blogs[i].name, blogs[i].category, blogs[i].content);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("No blog found with name \"%s\".\n", name);
    }
}


void writeBlogsToFile(Blog *blogs, int count) {
    FILE *file = fopen("blogs.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "Blog ID: %d\nname: %s\nCategory: %s\nContent: %s\n\n",
                blogs[i].id, blogs[i].name, blogs[i].category, blogs[i].content);
    }
    fclose(file);
    printf("All blogs have been written to blogs.txt\n");
}


void freeMemory(Blog **blogs) {
    free(*blogs);
    *blogs = NULL;
}
