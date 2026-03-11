all: $(NAME)
	@echo "$(GREEN)✅ Compilation terminée: $(NAME)$(RESET)"

bonus: $(BONUS_NAME)
	@echo "$(GREEN)✅ Compilation du bonus terminée: $(BONUS_NAME)$(RESET)"

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)
	@echo "$(CYAN)📁 Dossier obj créé.$(RESET)"

$(BONUS_OBJ_DIR):
	@$(MKDIR) $(BONUS_OBJ_DIR)
	@echo "$(CYAN)📁 Dossier obj_bonus créé.$(RESET)"

$(NAME): $(OBJ_DIR) $(OBJECTS)
	@echo "$(BLUE)🔗 Linkage de push_swap...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(GREEN)✨ $(NAME) créé avec succès!$(RESET)"

$(BONUS_NAME): $(BONUS_OBJ_DIR) $(BONUS_OBJECTS)
	@echo "$(BLUE)🔗 Linkage de checker...$(RESET)"
	@$(CC) $(CFLAGS) -I$(BONUS_DIR) $(BONUS_OBJECTS) -o $(BONUS_NAME)
	@echo "$(GREEN)✨ $(BONUS_NAME) créé avec succès!$(RESET)"

# Compilation rules for different source directories
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "$(YELLOW)🔧 Compilation: $<...$(RESET)"
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(OPS_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)🔧 Compilation: $<...$(RESET)"
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)🔧 Compilation: $<...$(RESET)"
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SORT_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)🔧 Compilation: $<...$(RESET)"
	@$(CC) -c $(CFLAGS) $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c | $(BONUS_OBJ_DIR)
	@echo "$(YELLOW)🔧 Compilation bonus: $<...$(RESET)"
	@$(CC) -c $(CFLAGS) -I$(BONUS_DIR) $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/utils/%.c | $(BONUS_OBJ_DIR)
	@echo "$(YELLOW)🔧 Compilation bonus: $<...$(RESET)"
	@$(CC) -c $(CFLAGS) -I$(BONUS_DIR) $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(UTILS_DIR)/%.c | $(BONUS_OBJ_DIR)
	@echo "$(YELLOW)🔧 Compilation bonus: $<...$(RESET)"
	@$(CC) -c $(CFLAGS) -I$(BONUS_DIR) $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(OPS_DIR)/%.c | $(BONUS_OBJ_DIR)
	@echo "$(YELLOW)🔧 Compilation bonus: $<...$(RESET)"
	@$(CC) -c $(CFLAGS) -I$(BONUS_DIR) $< -o $@

clean:
	@echo "$(RED)🧹 Suppression des fichiers objets...$(RESET)"
	@$(RM_RF) $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@echo "$(RED)✔️ Clean terminé.$(RESET)"

fclean: clean
	@echo "$(RED)🧨 Suppression des exécutables...$(RESET)"
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo "$(RED)✔️ Fclean terminé.$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re
