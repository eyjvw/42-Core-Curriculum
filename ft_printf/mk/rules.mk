all: $(NAME)
	@echo "$(GREEN)✅ Compilation completed: $(NAME)$(RESET)"

$(NAME): $(OBJECTS)
	@echo "$(BLUE)📦 Creating library...$(RESET)"
	@$(AR) $(NAME) $(OBJECTS)
	@echo "$(CYAN)📚 $(NAME) created successfully.$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@echo "$(YELLOW)🔧 Compiling $<...$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	@echo "$(RED)🧹 Removing object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)✔️ Clean done.$(RESET)"

fclean: clean
	@echo "$(RED)🧨 Removing library...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(RED)✔️ Fclean done.$(RESET)"

bonus: all

re: fclean
	@$(MAKE) --no-print-directory all

-include $(DEPS)

.PHONY: all bonus clean fclean re
