all: $(NAME)
	@echo "$(GREEN)✅ Compilation completed: $(NAME)$(RESET)"

bonus: $(NAME_BONUS)
	@echo "$(GREEN)✅ Bonus compilation completed: $(NAME_BONUS)$(RESET)"

$(NAME): $(OBJECTS)
	@echo "$(BLUE)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)
	@echo "$(CYAN)🚀 $(NAME) ready.$(RESET)"

$(NAME_BONUS): $(BONUS_OBJECTS)
	@echo "$(BLUE)🔗 Linking $(NAME_BONUS)...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME_BONUS) $(BONUS_OBJECTS)
	@echo "$(CYAN)🚀 $(NAME_BONUS) ready.$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@echo "$(YELLOW)🔧 Compiling $<...$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(PHILO_INC) -MMD -MP -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: %.c
	@echo "$(YELLOW)🔧 Compiling $<...$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(BONUS_INC) -MMD -MP -c $< -o $@

clean:
	@echo "$(RED)🧹 Removing object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@echo "$(RED)✔️ Clean done.$(RESET)"

fclean: clean
	@echo "$(RED)🧨 Removing binaries...$(RESET)"
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "$(RED)✔️ Fclean done.$(RESET)"

re: fclean
	@$(MAKE) --no-print-directory all

rebonus: fclean
	@$(MAKE) --no-print-directory bonus

-include $(DEPS)

.PHONY: all bonus clean fclean re rebonus
