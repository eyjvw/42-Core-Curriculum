all: $(MLX) $(NAME)
	@echo "$(GREEN)✅ Compilation completed: $(NAME)$(RESET)"

$(MLX):
	@echo "$(BLUE)📦 Building minilibx...$(RESET)"
	@cd $(MLX_DIR) && make

$(NAME): $(OBJ_DIR) $(OBJ_DIR)/utils $(OBJECTS)
	@echo "$(BLUE)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJECTS) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "$(CYAN)🚀 $(NAME) ready.$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/utils:
	@mkdir -p $(OBJ_DIR)/utils

$(OBJ_DIR)/%.o: %.c includes/so_long.h
	@echo "$(YELLOW)🔧 Compiling $<...$(RESET)"
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@echo "$(RED)🧹 Removing object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@cd $(MLX_DIR) && make clean
	@echo "$(RED)✔️ Clean done.$(RESET)"

fclean: clean
	@echo "$(RED)🧨 Removing binary...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(RED)✔️ Fclean done.$(RESET)"

re: fclean all

minilibx:
	@echo "$(BLUE)📥 Downloading minilibx...$(RESET)"
	@git clone https://github.com/42paris/minilibx-linux.git minilibx-linux
	@echo "$(GREEN)✅ minilibx-linux downloaded.$(RESET)"

.PHONY: all clean fclean re minilibx
