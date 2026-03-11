all: $(MLX) $(NAME)
	@echo "$(GREEN)Compilation terminee: $(NAME)$(RESET)"

$(MLX):
	@echo "$(BLUE)Compilation de minilibx...$(RESET)"
	@cd $(MLX_DIR) && make

$(NAME): $(OBJ_DIR) $(OBJ_DIR)/utils $(OBJECTS)
	@echo "$(BLUE)Linkage...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJECTS) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) cree.$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/utils:
	@mkdir -p $(OBJ_DIR)/utils

$(OBJ_DIR)/%.o: %.c includes/so_long.h
	@echo "$(YELLOW)Compilation: $<$(RESET)"
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@cd $(MLX_DIR) && make clean
	@echo "$(RED)Clean fait.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Fclean fait.$(RESET)"

re: fclean all

minilibx:
	@echo "$(BLUE)Telechargement de minilibx...$(RESET)"
	@git clone https://github.com/42paris/minilibx-linux.git minilibx-linux
	@echo "$(GREEN)minilibx-linux telecharge.$(RESET)"

.PHONY: all clean fclean re minilibx
