all: $(NAME)
	@echo "$(GREEN)✅ Compilation completed: $(NAME)$(RESET)"

$(NAME): $(MLX) $(OBJECTS)
	@echo "$(BLUE)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(MLX_FLAGS)
	@echo "$(CYAN)🚀 $(NAME) ready.$(RESET)"

$(MLX):
	@if [ ! -d $(MLX_DIR) ]; then \
		echo "$(BLUE)📥 Downloading minilibx...$(RESET)"; \
		git clone -q --depth 1 $(MLX_REPO) $(MLX_DIR); \
	fi
	@echo "$(BLUE)📦 Building minilibx...$(RESET)"
	@MAKEFLAGS= $(MAKE) -s -C $(MLX_DIR) > /dev/null 2>&1

$(OBJ_DIR)/%.o: %.c | $(MLX)
	@echo "$(YELLOW)🔧 Compiling $<...$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	@echo "$(RED)🧹 Removing object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@if [ -d $(MLX_DIR) ]; then MAKEFLAGS= $(MAKE) -s -C $(MLX_DIR) clean > /dev/null 2>&1; fi
	@echo "$(RED)✔️ Clean done.$(RESET)"

fclean: clean
	@echo "$(RED)🧨 Removing binary...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(RED)✔️ Fclean done.$(RESET)"

re: fclean
	@$(MAKE) --no-print-directory all

-include $(DEPS)

.PHONY: all clean fclean re
