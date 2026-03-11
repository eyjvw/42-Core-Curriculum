all: $(NAME)
	@echo "$(GREEN)✅ Compilation completed: $(NAME)$(RESET)"

$(NAME): $(OBJ_DIR) $(OBJ_DIR)/sources $(OBJECTS)
	@echo "$(BLUE)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)
	@echo "$(CYAN)🚀 $(NAME) ready.$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/sources:
	@mkdir -p $(OBJ_DIR)/sources

$(OBJ_DIR)/%.o: %.c includes/pipex.h
	@echo "$(YELLOW)🔧 Compiling $<...$(RESET)"
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@echo "$(RED)🧹 Removing object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)✔️  Clean done.$(RESET)"

fclean: clean
	@echo "$(RED)🧨 Removing binary...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(RED)✔️  Fclean done.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
